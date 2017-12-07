//
// Created by verrignij on 05/12/2017.
//

#ifndef OPENMINE_CAMERA_H
#define OPENMINE_CAMERA_H

#include <glm/detail/type_mat4x4.hpp>

class Camera
{
public:
    static void Init();
    static void Draw();
public:
    static glm::mat4 ProjectionMatrix;
    static glm::mat4 ViewMatrix;
    static glm::vec3 CameraLocation;
};

#endif //OPENMINE_CAMERA_H
