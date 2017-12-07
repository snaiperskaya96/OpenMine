#ifndef OPENMINE_CUBE_H
#define OPENMINE_CUBE_H

#include <Utils/FileSystem/File.h>
#include <Component/MeshComponent.h>
#include <Handler/Input/InputHandler.h>
#include "Entity.h"

class Cube : public Entity
{
public:
    Cube();
    void MoveForward();
};

Cube::Cube() : Entity()
{
    std::string Path = File::CreatePath(File::GetExecutableDir() + "/Objects/Cube/CubeTest.obj");
    for (auto Comp : MeshComponent::FromObj(Path))
        AddComponent(Comp);


//    InputHandler::OnKeyPress(GLFW_KEY_W, InputAction::KEY_REPEATED, this, &Cube::MoveForward);
}


void Cube::MoveForward()
{
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3{1.f, 0.0f, 0.0f});
}


#endif OPENMINE_CUBE_H
