//
// Created by verrignij on 05/12/2017.
//

#include <glm/ext.hpp>
#include <Handler/Input/InputHandler.h>
#include "Camera/Camera.h"

glm::mat4 Camera::ProjectionMatrix;
glm::mat4 Camera::ViewMatrix;
glm::vec3 Camera::CameraLocation;

void Camera::Init()
{
    CameraLocation = glm::vec3{4.f,3.f,3.f};
    ProjectionMatrix = glm::perspective(glm::radians(45.f), (SCREEN_WIDTH * 1.f)/(SCREEN_HEIGHT * 1.f), 0.1f, 100.f);
	ViewMatrix = glm::lookAt(CameraLocation, glm::vec3{ 0.f, 0.f, 0.f }, glm::vec3{ 0.f, 1.f, 0.f });

    InputHandler::OnKeyPress(GLFW_KEY_W, InputAction::KEY_PRESSED, nullptr, &Camera::MoveForward);
    InputHandler::OnKeyPress(GLFW_KEY_S, InputAction::KEY_PRESSED, nullptr, &Camera::MoveBackward);
    InputHandler::OnKeyPress(GLFW_KEY_A, InputAction::KEY_PRESSED, nullptr, &Camera::TurnLeft);
    InputHandler::OnKeyPress(GLFW_KEY_D, InputAction::KEY_PRESSED, nullptr, &Camera::TurnRight);
}

void Camera::Draw()
{

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