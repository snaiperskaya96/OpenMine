//
// Created by snaiperskaya on 03/12/17.
//
#include <Shader/Shader.h>
#include "GLFW/glfw3.h"
#include <iostream>
#include <Texture/Texture.h>
#include <glad/glad.h>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat2x2.hpp>
#include <glm/gtc/matrix_transform.inl>
#include "OpenMine.h"


GLFWwindow* OpenMine::Window;

void OpenMine::InitializeOpenGl()
{
    if (!glfwInit()) {
        std::cout << "Couldn't initialise GLFW." << std::endl;
        exit(1);
    }

    glfwSetErrorCallback(&OpenMine::GlfwErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void OpenMine::SetupWindow()
{
    Window = glfwCreateWindow(512, 512, "OpenMine", nullptr, nullptr);
    if (!Window) {
        std::cout << "Failed to initialize OpenGL Window." << std::endl;
        exit(1);
    }

    glfwSetKeyCallback(Window, &OpenMine::GlfwKeyCallback);

    glfwMakeContextCurrent(Window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    glClearColor(0.f, 0.f, 0.4f, 0.f);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void OpenMine::Init()
{
    Window = nullptr;

    InitializeOpenGl();
    SetupWindow();

    Shader Program(
            {
                    {"base-texture", ShaderType::Vertex},
                    {"base-texture", ShaderType::Fragment},
            }
    );

    Program.Link();

    const GLfloat Verticles[] = {
            -0.666667, -0.666667, -0.000000,
            1.333333, -0.666667, -0.000000,
            -0.666667, 1.333333, 0.000000,
    };

    const GLfloat UVs[] = {
            0.0, 0.5,
            0.500000, 0.0,
            0.5, 1.0,
    };

    const GLfloat Colors[] = {
            1.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            0.f, 0.f, 1.f
    };

    Program.Use();

    GLint CoordAttrib = glGetAttribLocation(Program.GetProgramId(), "Coordinates");
    GLint ColorAttrib = glGetAttribLocation(Program.GetProgramId(), "Color");
    GLint UvAttrib = glGetAttribLocation(Program.GetProgramId(), "Uv");
    GLint MvpUniform = glGetUniformLocation(Program.GetProgramId(), "Mvp");
    GLint TextureUniform = glGetUniformLocation(Program.GetProgramId(), "Texture");

    GLuint BufferId;
    glGenBuffers(1, &BufferId);
    glBindBuffer(GL_ARRAY_BUFFER, BufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Verticles), &Verticles[0], GL_STATIC_DRAW);

    GLuint ColorId;
    glGenBuffers(1, &ColorId);
    glBindBuffer(GL_ARRAY_BUFFER, ColorId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), &Colors[0], GL_STATIC_DRAW);

    GLuint UvId;
    glGenBuffers(1, &UvId);
    glBindBuffer(GL_ARRAY_BUFFER, UvId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(UVs), &UVs[0], GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    glBindBuffer( GL_ARRAY_BUFFER, BufferId );
    glVertexAttribPointer(CoordAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glEnableVertexAttribArray(CoordAttrib);

    glBindBuffer( GL_ARRAY_BUFFER, ColorId );
    glVertexAttribPointer(ColorAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glEnableVertexAttribArray(ColorAttrib);

    glBindBuffer( GL_ARRAY_BUFFER, UvId );
    glVertexAttribPointer(UvAttrib, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glEnableVertexAttribArray(UvAttrib);

    auto Model = glm::mat4(1.f);
    auto View = glm::lookAt(glm::vec3(4.f,3.f,3.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    auto Projection = glm::perspective(glm::radians(45.f), 4.0f/3.0f, 0.1f, 100.f);

    auto Tex = Texture::FromName("layout.png");

    while (!glfwWindowShouldClose(Window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Program.Use();

        glBindVertexArray( vao );

        glm::mat4 MvpMat = Projection * View * Model;

        glUniformMatrix4fv(MvpUniform, 1, GL_FALSE, &MvpMat[0][0]);
        Tex->Bind(TextureUniform);

        glDrawArrays(GL_TRIANGLES, 0, sizeof(Verticles)/3);

        if (glfwGetKey(Window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            //glm::rotate(View, 10.f, {0.f, 1.f, 0.f});
            Model = glm::translate(Model, {0.f, 0.f, -.1f});
        }
        if (glfwGetKey(Window, GLFW_KEY_UP) == GLFW_PRESS) {
            //glm::rotate(View, 10.f, {0.f, 1.f, 0.f});
            Model = glm::translate(Model, {0.f, 0.f, .1f});
        }
        if (glfwGetKey(Window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            Model = glm::rotate(Model, glm::radians(10.f), {0.f, 1.f, 0.f});
        }

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

