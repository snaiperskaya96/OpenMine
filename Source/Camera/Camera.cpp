//
// Created by verrignij on 05/12/2017.
//

#include <glm/ext.hpp>
#include <Handler/Input/InputHandler.h>
#include <OpenMine/OpenMine.h>
#include "Camera/Camera.h"

glm::mat4 Camera::ProjectionMatrix;
glm::mat4 Camera::ViewMatrix;
glm::vec3 Camera::CameraLocation;
glm::vec3 Camera::CameraTarget;
glm::vec3 Camera::CameraDirection;
glm::vec3 Camera::CameraUp;
glm::vec3 Camera::CameraRight;
glm::vec3 Camera::Up;
glm::vec3 Camera::CameraFront;
float Camera::LastFrame;
float Camera::DeltaTime;
float Camera::MouseX;
float Camera::MouseY;
float Camera::Yaw;
float Camera::Pitch;
bool Camera::FirstMouseInput;

void Camera::Init()
{
    LastFrame = DeltaTime = 0.f;
    MouseX = MouseY = 0.f;
    Pitch = Yaw = 0.f;
    FirstMouseInput = true;

    CameraLocation = glm::vec3{1.f, 1.f, 1.f};
    CameraTarget = glm::vec3{0.0f, 0.0f, 0.0f};
    Up = glm::vec3{0.0f, 1.0f, 0.0f};
    CameraFront = glm::vec3{0.0f, 0.0f, -1.0f};

    CameraDirection = glm::normalize(CameraLocation - CameraTarget);
    CameraRight = glm::normalize(glm::cross(Up, CameraDirection));
    CameraUp = glm::cross(CameraDirection, CameraRight);
    ProjectionMatrix = glm::perspective(glm::radians(45.f), (SCREEN_WIDTH * 1.f)/(SCREEN_HEIGHT * 1.f), 0.1f, 100.f);

    InputHandler::OnMouseMove(nullptr, &Camera::OnMouseMove);
}

void Camera::OnMouseMove(float X, float Y)
{
    float XOffset = X - MouseX;
    float YOffset = MouseY - Y; // reversed since y-coordinates range from bottom to top
    MouseX = X;
    MouseY = Y;

    if (FirstMouseInput) {
        FirstMouseInput = false;
        return;
    }

    float Sensitivity = 0.05f;
    XOffset *= Sensitivity;
    YOffset *= Sensitivity;

    Yaw   += XOffset;
    Pitch += YOffset;

    if(Pitch > 89.0f)
        Pitch =  89.0f;
    if(Pitch < -89.0f)
        Pitch = -89.0f;

    glm::vec3 Front = {0.f, 0.f, 0.f};
    Front.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
    Front.y = sin(glm::radians(Pitch));
    Front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
    CameraFront = glm::normalize(Front);
}

void Camera::Draw()
{
    auto CurrentFrame = (float) glfwGetTime();
    DeltaTime = CurrentFrame - LastFrame;
    glfwSetWindowTitle(OpenMine::GetWindow(), ("DeltaTime: " + std::to_string(DeltaTime) + " - FPS: " + std::to_string(1.f / DeltaTime)).c_str());
    LastFrame = CurrentFrame;
    float CameraSpeed = 2.5f * DeltaTime;

    ViewMatrix = glm::lookAt(CameraLocation, CameraLocation + CameraFront, CameraUp);

    if (glfwGetKey(OpenMine::GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
        Camera::CameraLocation += CameraSpeed * Camera::CameraFront;
    if (glfwGetKey(OpenMine::GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
        Camera::CameraLocation -= CameraSpeed * Camera::CameraFront;
    if (glfwGetKey(OpenMine::GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
        Camera::CameraLocation -= glm::normalize(glm::cross(Camera::CameraFront, Camera::CameraUp)) * CameraSpeed;
    if (glfwGetKey(OpenMine::GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
        Camera::CameraLocation += glm::normalize(glm::cross(Camera::CameraFront, Camera::CameraUp)) * CameraSpeed;
}

void Camera::MoveForward()
{
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3{0.f, 0.f, 1.f});
}

void Camera::MoveBackward()
{
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3{0.f, 0.f, -1.f});
}

void Camera::TurnLeft()
{
    ViewMatrix = glm::rotate(ViewMatrix, glm::radians(-1.f), glm::vec3{0.f, 1.f, 0.f});
}

void Camera::TurnRight()
{
    ViewMatrix = glm::rotate(ViewMatrix, glm::radians(1.f), glm::vec3{0.f, 1.f, 0.f});
}