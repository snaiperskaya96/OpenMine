//
// Created by verrignij on 05/12/2017.
//

#include <glm/ext.hpp>
#include "Camera/Camera.h"

glm::mat4 Camera::ProjectionMatrix;
glm::mat4 Camera::ViewMatrix;
glm::vec3 Camera::CameraLocation;

void Camera::Init()
{
    CameraLocation = glm::vec3{4.f,3.f,3.f};
    ProjectionMatrix = glm::perspective(glm::radians(45.f), 16.f/9.f, 0.1f, 100.f);
	ViewMatrix = glm::lookAt(CameraLocation, glm::vec3{ 0.f, 0.f, 0.f }, glm::vec3{ 0.f, 1.f, 0.f });
}

void Camera::Draw()
{
}