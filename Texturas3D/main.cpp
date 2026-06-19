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

out vec2 TexCoord;

uniform float angle;

void main()
{
    mat4 rotation = mat4(
        cos(angle), 0.0, sin(angle), 0.0,
        0.0,       1.0, 0.0,        0.0,
       -sin(angle),0.0, cos(angle),0.0,
        0.0,       0.0, 0.0,        1.0
    );

    gl_Position = rotation * vec4(aPos, 1.0);

    TexCoord = aTex;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoord);
}
)";

int main()
{
    glfwInit();

    GLFWwindow* window =
        glfwCreateWindow(
            800,
            600,
            "Cubo Texturizado",
            NULL,
            NULL
        );

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    glewInit();

    glEnable(GL_DEPTH_TEST);

    float vertices[] =
    {
        // posiciones           // UV

        // Frente
        -0.5f,-0.5f, 0.5f,      0.0f,0.0f,
         0.5f,-0.5f, 0.5f,      1.0f,0.0f,
         0.5f, 0.5f, 0.5f,      1.0f,1.0f,
        -0.5f, 0.5f, 0.5f,      0.0f,1.0f,

        // Atrás
        -0.5f,-0.5f,-0.5f,      1.0f,0.0f,
         0.5f,-0.5f,-0.5f,      0.0f,0.0f,
         0.5f, 0.5f,-0.5f,      0.0f,1.0f,
        -0.5f, 0.5f,-0.5f,      1.0f,1.0f
    };

    unsigned int indices[] =
    {
        // Frente
        0,1,2,
        2,3,0,

        // Atrás
        4,5,6,
        6,7,4,

        // Izquierda
        4,0,3,
        3,7,4,

        // Derecha
        1,5,6,
        6,2,1,

        // Arriba
        3,2,6,
        6,7,3,

        // Abajo
        4,5,1,
        1,0,4
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

    // Posiciones
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        5*sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    // UV
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        5*sizeof(float),
        (void*)(3*sizeof(float))
    );

    glEnableVertexAttribArray(1);

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

    // ===== TEXTURA =====

    GLuint texture;

    glGenTextures(1,&texture);

    glBindTexture(GL_TEXTURE_2D,texture);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    stbi_set_flip_vertically_on_load(true);

    int width,height,nrChannels;

    unsigned char* data =
        stbi_load(
            "textura2.jpg",
            &width,
            &height,
            &nrChannels,
            0
        );

    if(data)
    {
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            width,
            height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            data
        );

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Error textura\n";
    }

    stbi_image_free(data);

    // ===== LOOP =====

    while(!glfwWindowShouldClose(window))
    {
        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );

        float time =
            glfwGetTime();

        glUseProgram(shaderProgram);

        GLuint angleLoc =
            glGetUniformLocation(
                shaderProgram,
                "angle"
            );

        glUniform1f(angleLoc,time);

        glBindTexture(GL_TEXTURE_2D,texture);

        glBindVertexArray(VAO);

        glDrawElements(
            GL_TRIANGLES,
            36,
            GL_UNSIGNED_INT,
            0
        );

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

