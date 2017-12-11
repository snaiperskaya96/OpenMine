//
// Created by snaiperskaya on 03/12/17.
//
#include <Shader/Shader.h>
#include "GLFW/glfw3.h"
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat2x2.hpp>
#include <Camera/Camera.h>
#include <Pool/EntityPool.h>
#include <glm/ext.hpp>
#include <Entity/Cube.h>
#include <Handler/Input/InputHandler.h>
#include <Entity/Chunk/Chunk.h>
#include <Utils/Thread/AsyncTask.h>
#include <Handler/Terrain/TerrainHandler.h>
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
    glfwSwapInterval(-1);

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


   // T2.Initialise();
   // T2.SetRelativeLocation({1.2f, -1.0f, 0.5f});
    TerrainHandler::BuildChunksAroundCoords(Camera::CameraLocation);
//    new Chunk();

    InputHandler::SetInputMode(InputMode::CURSOR, InputModeValue::CURSOR_DISABLED);

    while (!glfwWindowShouldClose(Window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Camera::Draw();
        EntityPool::Draw();

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


