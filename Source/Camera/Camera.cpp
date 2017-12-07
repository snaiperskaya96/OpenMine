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

void Camera::Init()
{
    CameraTarget = glm::vec3{0.0f, 0.0f, 0.0f};
    CameraDirection = glm::normalize(CameraLocation - CameraTarget);

    Up = glm::vec3{0.0f, 1.0f, 0.0f};
    CameraRight = glm::normalize(glm::cross(Up, CameraDirection));
    CameraUp = glm::cross(CameraDirection, CameraRight);

    CameraLocation = glm::vec3{1.f, 1.f, 1.f};
    ProjectionMatrix = glm::perspective(glm::radians(45.f), (SCREEN_WIDTH * 1.f)/(SCREEN_HEIGHT * 1.f), 0.1f, 100.f);
    //ViewMatrix = glm::lookAt(CameraLocation, glm::vec3{ 0.f, 0.f, 0.f }, glm::vec3{ 0.f, 1.f, 0.f });

    ViewMatrix = glm::lookAt(glm::vec3{0.0f, 0.0f, 3.0f},
                             glm::vec3{0.0f, 0.0f, 0.0f},
                             glm::vec3{0.0f, 1.0f, 0.0f});

    CameraFront = glm::vec3{0.0f, 0.0f, -1.0f};

/*    InputHandler::OnKeyPress(GLFW_KEY_W, InputAction::KEY_PRESSED, nullptr, &Camera::MoveForward);
    InputHandler::OnKeyPress(GLFW_KEY_S, InputAction::KEY_PRESSED, nullptr, &Camera::MoveBackward);
    InputHandler::OnKeyPress(GLFW_KEY_A, InputAction::KEY_PRESSED, nullptr, &Camera::TurnLeft);
    InputHandler::OnKeyPress(GLFW_KEY_D, InputAction::KEY_PRESSED, nullptr, &Camera::TurnRight);
*/
    //https://learnopengl.com/#!Getting-started/Camera
}

void Camera::Draw()
{
    ViewMatrix = glm::lookAt(CameraLocation, CameraLocation + CameraFront, CameraUp);
    float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(OpenMine::GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
        Camera::CameraLocation += cameraSpeed * Camera::CameraFront;
    if (glfwGetKey(OpenMine::GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
        Camera::CameraLocation -= cameraSpeed * Camera::CameraFront;
    if (glfwGetKey(OpenMine::GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
        Camera::CameraLocation -= glm::normalize(glm::cross(Camera::CameraFront, Camera::CameraUp)) * cameraSpeed;
    if (glfwGetKey(OpenMine::GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
        Camera::CameraLocation += glm::normalize(glm::cross(Camera::CameraFront, Camera::CameraUp)) * cameraSpeed;

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