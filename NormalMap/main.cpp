#include <windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <cmath>
#include <string>
#include <vector>

struct TextureSet
{
    const char* name;
    const char* diffusePath;
    const char* bumpPath;
    GLuint diffuseTexture;
    GLuint bumpTexture;
};

struct AppState
{
    std::vector<TextureSet>* textures;
    int currentTexture;
    double lastTextureChange;
    double autoInterval;
};

const char* vertexShaderSource = R"(
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;
layout(location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform float angle;

void main()
{
    mat4 rotation = mat4(
        cos(angle), 0.0, sin(angle), 0.0,
        0.0,       1.0, 0.0,        0.0,
       -sin(angle),0.0, cos(angle),0.0,
        0.0,       0.0, 0.0,        1.0
    );

    vec4 worldPos = rotation * vec4(aPos,1.0);

    FragPos = vec3(worldPos);

    Normal = mat3(rotation) * aNormal;

    gl_Position = worldPos;

    TexCoord = aTex;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D diffuseMap;
uniform sampler2D bumpMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // ===== TEXTURA BASE =====
    vec3 color =
        texture(diffuseMap, TexCoord).rgb;

    // ===== BUMP MAP =====
    float height =
        texture(bumpMap, TexCoord).r;

    // Perturbar normal
    vec3 bumpedNormal =
        normalize(
            Normal +
            vec3(height * 0.3)
        );

    // ===== PHONG =====

    // Ambient
    vec3 ambient =
        0.2 * color;

    // Diffuse
    vec3 lightDir =
        normalize(lightPos - FragPos);

    float diff =
        max(dot(bumpedNormal, lightDir),0.0);

    vec3 diffuse =
        diff * color;

    // Specular
    vec3 viewDir =
        normalize(viewPos - FragPos);

    vec3 reflectDir =
        reflect(-lightDir, bumpedNormal);

    float spec =
        pow(max(dot(viewDir,reflectDir),0.0),32);

    vec3 specular =
        vec3(0.5) * spec;

    vec3 result =
        ambient + diffuse + specular;

    FragColor =
        vec4(result,1.0);
}
)";

GLuint loadTexture(const char* path)
{
    GLuint textureID;

    glGenTextures(1, &textureID);

    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* data =
        stbi_load(
            path,
            &width,
            &height,
            &nrChannels,
            0
        );

    glBindTexture(GL_TEXTURE_2D, textureID);

    if(data)
    {
        GLenum format =
            nrChannels == 4
            ? GL_RGBA
            : GL_RGB;

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            format,
            width,
            height,
            0,
            format,
            GL_UNSIGNED_BYTE,
            data
        );

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Error textura\n";
    }

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    stbi_image_free(data);

    return textureID;
}

void selectTexture(
    GLFWwindow* window,
    const std::vector<TextureSet>& textures,
    int& currentTexture,
    int nextTexture
)
{
    if(
        nextTexture < 0 ||
        nextTexture >= (int)textures.size() ||
        nextTexture == currentTexture
    )
    {
        return;
    }

    currentTexture = nextTexture;

    std::string title =
        std::string("Bump Mapping - ") +
        textures[currentTexture].name;

    glfwSetWindowTitle(
        window,
        title.c_str()
    );

    std::cout
        << "Textura activa: "
        << currentTexture + 1
        << " - "
        << textures[currentTexture].name
        << "\n";
}

void changeTexture(
    GLFWwindow* window,
    AppState* state,
    int direction
)
{
    if(
        state == NULL ||
        state->textures == NULL ||
        state->textures->empty()
    )
    {
        return;
    }

    std::vector<TextureSet>& textures =
        *state->textures;

    int total =
        (int)textures.size();

    int nextTexture =
        (state->currentTexture + direction + total) %
        total;

    selectTexture(
        window,
        textures,
        state->currentTexture,
        nextTexture
    );

    state->lastTextureChange =
        glfwGetTime();
}

void mouseButtonCallback(
    GLFWwindow* window,
    int button,
    int action,
    int mods
)
{
    (void)mods;

    if(action != GLFW_PRESS)
    {
        return;
    }

    AppState* state =
        (AppState*)glfwGetWindowUserPointer(window);

    if(button == GLFW_MOUSE_BUTTON_LEFT)
    {
        changeTexture(
            window,
            state,
            1
        );
    }
    else if(button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        changeTexture(
            window,
            state,
            -1
        );
    }
}

void scrollCallback(
    GLFWwindow* window,
    double xoffset,
    double yoffset
)
{
    (void)xoffset;

    AppState* state =
        (AppState*)glfwGetWindowUserPointer(window);

    if(yoffset > 0.0)
    {
        changeTexture(
            window,
            state,
            1
        );
    }
    else if(yoffset < 0.0)
    {
        changeTexture(
            window,
            state,
            -1
        );
    }
}

void keyCallback(
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int mods
)
{
    (void)scancode;
    (void)mods;

    if(action != GLFW_PRESS && action != GLFW_REPEAT)
    {
        return;
    }

    if(key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    AppState* state =
        (AppState*)glfwGetWindowUserPointer(window);

    if(
        state == NULL ||
        state->textures == NULL ||
        state->textures->empty()
    )
    {
        return;
    }

    std::vector<TextureSet>& textures =
        *state->textures;

    int total =
        (int)textures.size();

    if(key == GLFW_KEY_RIGHT || key == GLFW_KEY_D)
    {
        selectTexture(
            window,
            textures,
            state->currentTexture,
            (state->currentTexture + 1) % total
        );

        return;
    }

    if(key == GLFW_KEY_LEFT || key == GLFW_KEY_A)
    {
        selectTexture(
            window,
            textures,
            state->currentTexture,
            (state->currentTexture + total - 1) % total
        );

        return;
    }

    int selectedTexture = -1;

    if(key >= GLFW_KEY_1 && key <= GLFW_KEY_9)
    {
        selectedTexture = key - GLFW_KEY_1;
    }
    else if(key >= GLFW_KEY_KP_1 && key <= GLFW_KEY_KP_9)
    {
        selectedTexture = key - GLFW_KEY_KP_1;
    }

    if(selectedTexture >= 0 && selectedTexture < total)
    {
        selectTexture(
            window,
            textures,
            state->currentTexture,
            selectedTexture
        );

        return;
    }
}

int main()
{
    glfwInit();

    GLFWwindow* window =
        glfwCreateWindow(
            800,
            600,
            "Bump Mapping",
            NULL,
            NULL
        );

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    glewInit();

    glEnable(GL_DEPTH_TEST);

    float vertices[] =
    {
        // Posiciones      // UV      // Normales

        -0.5f,-0.5f,0.0f, 0.0f,0.0f, 0.0f,0.0f,1.0f,
         0.5f,-0.5f,0.0f, 1.0f,0.0f, 0.0f,0.0f,1.0f,
         0.5f, 0.5f,0.0f, 1.0f,1.0f, 0.0f,0.0f,1.0f,
        -0.5f, 0.5f,0.0f, 0.0f,1.0f, 0.0f,0.0f,1.0f
    };

    unsigned int indices[] =
    {
        0,1,2,
        2,3,0
    };

    GLuint VAO,VBO,EBO;

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_STATIC_DRAW
    );

    // Posición
    glVertexAttribPointer(
        0,3,GL_FLOAT,GL_FALSE,
        8*sizeof(float),(void*)0
    );

    glEnableVertexAttribArray(0);

    // UV
    glVertexAttribPointer(
        1,2,GL_FLOAT,GL_FALSE,
        8*sizeof(float),
        (void*)(3*sizeof(float))
    );

    glEnableVertexAttribArray(1);

    // Normales
    glVertexAttribPointer(
        2,3,GL_FLOAT,GL_FALSE,
        8*sizeof(float),
        (void*)(5*sizeof(float))
    );

    glEnableVertexAttribArray(2);

    // ===== SHADERS =====

    GLuint vertexShader =
        glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(
        vertexShader,
        1,
        &vertexShaderSource,
        NULL
    );

    glCompileShader(vertexShader);

    GLuint fragmentShader =
        glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(
        fragmentShader,
        1,
        &fragmentShaderSource,
        NULL
    );

    glCompileShader(fragmentShader);

    GLuint shaderProgram =
        glCreateProgram();

    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);

    glLinkProgram(shaderProgram);

    // ===== TEXTURAS =====

    std::vector<TextureSet> textures =
    {
        {
            "Bloques de piedra",
            "textura_color.jpg",
            "textura_bump.jpg",
            0,
            0
        },
        {
            "Madera",
            "madera_color.jpg",
            "madera_bump.jpg",
            0,
            0
        },
        {
            "Piedra redonda",
            "piedraN.png",
            "piedraB.png",
            0,
            0
        },
        {
            "Ladrillo",
            "ladrillo_color.jpg",
            "ladrillo_bump.jpg",
            0,
            0
        },
        {
            "Metal cepillado",
            "metal_color.jpg",
            "metal_bump.jpg",
            0,
            0
        }
    };

    for(int i = 0; i < (int)textures.size(); i++)
    {
        textures[i].diffuseTexture =
            loadTexture(textures[i].diffusePath);

        textures[i].bumpTexture =
            loadTexture(textures[i].bumpPath);
    }

    AppState state =
    {
        &textures,
        0,
        glfwGetTime(),
        10.0
    };

    glfwSetWindowUserPointer(
        window,
        &state
    );

    glfwSetKeyCallback(
        window,
        keyCallback
    );

    glfwSetMouseButtonCallback(
        window,
        mouseButtonCallback
    );

    glfwSetScrollCallback(
        window,
        scrollCallback
    );

    glfwSetWindowTitle(
        window,
        "Bump Mapping - Bloques de piedra"
    );

    std::cout
        << "Texturas cargadas:\n"
        << "1 Bloques de piedra\n"
        << "2 Madera\n"
        << "3 Piedra redonda\n"
        << "4 Ladrillo\n"
        << "5 Metal cepillado\n"
        << "Cambio automatico cada 10 segundos\n"
        << "Click izquierdo: siguiente textura\n"
        << "Click derecho: textura anterior\n"
        << "Rueda del mouse: cambiar textura\n";

    // ===== LOOP =====

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        if(
            glfwGetTime() - state.lastTextureChange >=
            state.autoInterval
        )
        {
            changeTexture(
                window,
                &state,
                1
            );
        }

        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );

        glUseProgram(shaderProgram);

        glUniform1f(
            glGetUniformLocation(
                shaderProgram,
                "angle"
            ),
            glfwGetTime()
        );

        glUniform3f(
            glGetUniformLocation(
                shaderProgram,
                "lightPos"
            ),
            1.0f,
            1.0f,
            2.0f
        );

        glUniform3f(
            glGetUniformLocation(
                shaderProgram,
                "viewPos"
            ),
            0.0f,
            0.0f,
            2.0f
        );

        // Textura difusa
        glActiveTexture(GL_TEXTURE0);

        glBindTexture(
            GL_TEXTURE_2D,
            textures[state.currentTexture].diffuseTexture
        );

        glUniform1i(
            glGetUniformLocation(
                shaderProgram,
                "diffuseMap"
            ),
            0
        );

        // Bump map
        glActiveTexture(GL_TEXTURE1);

        glBindTexture(
            GL_TEXTURE_2D,
            textures[state.currentTexture].bumpTexture
        );

        glUniform1i(
            glGetUniformLocation(
                shaderProgram,
                "bumpMap"
            ),
            1
        );
        glBindVertexArray(VAO);

        glDrawElements(
            GL_TRIANGLES,
            6,
            GL_UNSIGNED_INT,
            0
        );

        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
