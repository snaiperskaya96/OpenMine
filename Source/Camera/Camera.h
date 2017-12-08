//
// Created by verrignij on 05/12/2017.
//

#ifndef OPENMINE_CAMERA_H
#define OPENMINE_CAMERA_H

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#include <glm/detail/type_mat4x4.hpp>

class Camera
{
public:
    static void Init();
    static void Draw();
    static void OnMouseMove(float X, float Y);
protected:
    static void MoveForward();
    static void MoveBackward();
    static void TurnLeft();
    static void TurnRight();
public:
    static glm::mat4 ProjectionMatrix;
    static glm::mat4 ViewMatrix;
    static glm::vec3 CameraLocation;
    static glm::vec3 CameraTarget;
    static glm::vec3 CameraDirection;
    static glm::vec3 Up;
    static glm::vec3 CameraRight;
    static glm::vec3 CameraUp;
    static glm::vec3 CameraFront;
    static float DeltaTime;
    static float MouseX;
    static float MouseY;
    static float Yaw;
    static float Pitch;
protected:
    static float LastFrame;
    static bool FirstMouseInput;
};

#endif //OPENMINE_CAMERA_H
