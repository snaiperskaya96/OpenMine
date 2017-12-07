//
// Created by snaiperskaya on 03/12/17.
//
#include <Shader/Shader.h>
#include "GLFW/glfw3.h"
#include <Texture/Texture.h>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat2x2.hpp>
#include <Camera/Camera.h>
#include <Pool/EntityPool.h>
#include <glm/ext.hpp>
#include "OpenMine.h"
#include "Entity/Triangle.h"


GLFWwindow* OpenMine::Window;

void OpenMine::InitializeOpenGl()
{
    if (!glfwInit()) {
        std::cout << "Couldn't initialise GLFW." << std::endl;
        exit(1);
    }

    glfwSetErrorCallback(&OpenMine::GlfwErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
}

void OpenMine::GlDebugMessage(GLenum Source, GLenum Type, GLuint Id, GLenum Severity, GLsizei Length, const GLchar* Message, const void* UserParam)
{
	std::cout << "OpenGL Debug Message received: " << Message << std::endl;
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

    //glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glDebugMessageCallback(&OpenMine::GlDebugMessage, nullptr);
}

/* ... */

void OpenMine::Init()
{
    Window = nullptr;

    InitializeOpenGl();
    SetupWindow();

    Camera::ViewMatrix = glm::lookAt(glm::vec3{4.f,3.f,3.f}, glm::vec3{0.f, 0.f, 0.f}, glm::vec3{0.f, 1.f, 0.f});
    Camera::ProjectionMatrix = glm::perspective(glm::radians(45.f), 4.0f/3.0f, 0.1f, 100.f);

    EntityPool::Init();

    Triangle T, T2;
    T.Initialise();
    T2.Initialise();
    T2.SetRelativeLocation({1.2f, -1.0f, 0.5f});

    while (!glfwWindowShouldClose(Window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        EntityPool::Draw();

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

