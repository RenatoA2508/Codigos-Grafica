#include <windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <cmath>

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

    GLuint diffuseTexture =
        loadTexture("textura_color.jpg");




    GLuint bumpTexture =
        loadTexture("textura_bump.jpg");

    // ===== LOOP =====

    while(!glfwWindowShouldClose(window))
    {
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
            diffuseTexture
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
            bumpTexture
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

        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
