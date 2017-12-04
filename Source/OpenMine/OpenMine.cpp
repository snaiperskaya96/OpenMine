//
// Created by snaiperskaya on 03/12/17.
//
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <iostream>
#include <Shader/Shader.h>
#include <Texture/Texture.h>
#include "OpenMine.h"
#include "linmath.h"

GLFWwindow* OpenMine::Window;

/*static const struct
{
    float x, y, z;
    float r, g, b;
} Verticles[6] = {
        {-.75f, .75f, 1.f, 1.f, 0.f, 0.f},
        {.75f, .75f, 1.f, 0.f, 1.f, 0.f},
        {.75f, -.75f, 1.f, 0.f, 0.f, 1.f},
        {-.75f, .75f, 1.f, 1.f, 0.f, 0.f},
        {-.75f, -.75f, 1.f, 0.f, 1.f, 0.f},
        {.75f, -.75f, 1.f, 0.f, 0.f, 1.f},
};*/

static const struct
{
    float x, y, z;
    float u, v;
} Verticles[6] = {
        {-.75f, .75f, 1.f, 0.f, 1.f},
        {.75f, .75f, 1.f, 1.f, 1.f},
        {.75f, -.75f, 1.f, 1.f, 0.f},
        {-.75f, .75f, 1.f, 0.f, 1.f},
        {-.75f, -.75f, 1.f, 0.f, 0.f},
        {.75f, -.75f, 1.f, 1.f, 0.f},
};

void OpenMine::Init()
{
    Window = nullptr;

    if (!glfwInit()) {
        std::cout << "Couldn't initialise GLFW." << std::endl;
        exit(1);
    }

    glfwSetErrorCallback(&OpenMine::GlfwErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    Window = glfwCreateWindow(512, 512, "OpenMine", nullptr, nullptr);
    if (!Window) {
        std::cout << "Couldn't initialise OpenGL Window." << std::endl;
        exit(1);
    }

    glfwSetKeyCallback(Window, &OpenMine::GlfwKeyCallback);

    glfwMakeContextCurrent(Window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    GLuint VertexBuf = 0;
    glGenBuffers(1, &VertexBuf);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Verticles), Verticles, GL_STATIC_DRAW);

    Shader S(
            {
                    {"base-texture", ShaderType::Vertex},
                    {"base-texture", ShaderType::Fragment},
            }
    );

    S.Link();


    GLint MvpLocation = glGetUniformLocation(S.GetProgramId(), "MVP");
    GLint VertexPositionLocation = glGetAttribLocation(S.GetProgramId(), "Coordinates");
    GLint ColorLocation = glGetAttribLocation(S.GetProgramId(), "TextureCoordinates");
    auto Tex = Texture::FromName("texture.png");

    S.Use();

    Tex->Bind();

    S.SetUniform("Texture", 0);


    glEnableVertexAttribArray((GLuint)VertexPositionLocation);
    glVertexAttribPointer((GLuint)VertexPositionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) 0);
    glEnableVertexAttribArray((GLuint)ColorLocation);
    glVertexAttribPointer((GLuint)ColorLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (sizeof(float) * 3));

    const GLubyte* Version = glGetString(GL_VERSION);
    std::cout << "Using openGL version: " << Version << std::endl;


    while (!glfwWindowShouldClose(Window)) {
        float Ratio;
        int Width, Height;

        mat4x4 M, P, Mvp;

        glfwGetFramebufferSize(Window, &Width, &Height);
        Ratio = Width / Height;
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.f, 0.f, 0.4f, 0.f);

        /*mat4x4_identity(M);
        mat4x4_rotate_Z(M, M, (float) glfwGetTime());
        mat4x4_ortho(P, -Ratio, Ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(Mvp, P, M);
*/
        mat4x4_identity(Mvp);
        glUniformMatrix4fv(MvpLocation, 1, GL_FALSE, (const GLfloat*) Mvp);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(Window);
        glfwPollEvents();
    }

    glfwDestroyWindow(Window);
    glfwTerminate();
}

void OpenMine::GlfwErrorCallback(int Error, const char* Description)
{
    std::cout << "GLFW returned an error (" << Error << "): " << Description << std::endl;
}

void OpenMine::GlfwKeyCallback(struct GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
    if (Key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(Window, true);
    }
}