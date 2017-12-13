//
// Created by snaiperskaya on 03/12/17.
//
#include <iostream>
#include <Camera/Camera.h>
#include <Handler/Input/InputHandler.h>
#include <Pool/EntityPool.h>
#include <Entity/Cube/Cube.h>
#include <Utils/Thread/AsyncTask.h>
#include "glm/gtx/transform.hpp"
#include <Renderer/Cube/CubeRenderer.h>
#include "OpenMine.h"

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
    Window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenMine", nullptr, nullptr);
    if (!Window) {
        std::cout << "Failed to initialize OpenGL Window." << std::endl;
        exit(1);
    }

    InputHandler::Init(Window);

    glfwMakeContextCurrent(Window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(0);

    glClearColor(0.20f, 0.25f, 0.25f, 0.f);

    //glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    //glDebugMessageCallback(&OpenMine::GlDebugMessage, nullptr);
}

/* ... */

void OpenMine::Init()
{
    Window = nullptr;

    InitializeOpenGl();
    SetupWindow();

    Camera::Init();
    Camera::SetLocation({4.f, 4.f, 4.f});
    EntityPool::Init();

    for (int x = 0; x < 16; x++)
        for (int z = 0; z < 16; z++)
            for (int y = 0; y < 16; y++) {
            auto C = new Cube();
            C->SetRelativeLocation({2*x, 2*y, 2*z});
        }

    InputHandler::SetInputMode(InputMode::CURSOR, InputModeValue::CURSOR_DISABLED);

    while (!glfwWindowShouldClose(Window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Camera::Draw();
        //EntityPool::Draw();
        CubeRenderer::GetInstance()->Draw();

        if (AsyncTask::IsTaskAvailable(TaskThread::GAME_THREAD)) {
            AsyncTask::GetTaskFromQueue(TaskThread::GAME_THREAD)();
        }

        glfwSwapBuffers(Window);
        glfwPollEvents();

        if(glfwGetKey(OpenMine::GetWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
            Camera::ViewMatrix = glm::translate(Camera::ViewMatrix, glm::vec3{0.0f, 0.f, 0.1f});
        }
        if(glfwGetKey(OpenMine::GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
            Camera::ViewMatrix = glm::translate(Camera::ViewMatrix, glm::vec3{0.0f, 0.f, -0.1f});
        }
        if(glfwGetKey(OpenMine::GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
            Camera::ViewMatrix = glm::rotate(Camera::ViewMatrix, glm::radians(1.f), glm::vec3{0.0f, 1.f, 0.f});
        }
        if(glfwGetKey(OpenMine::GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
            Camera::ViewMatrix = glm::rotate(Camera::ViewMatrix, glm::radians(1.f), glm::vec3{0.0f, -1.f, 0.f});
        }
    }

    glfwDestroyWindow(Window);
    glfwTerminate();
}

void OpenMine::GlfwErrorCallback(int Error, const char* Description)
{
    std::cout << "GLFW returned an error (" << Error << "): " << Description << std::endl;
}


