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
    void Draw() override;
};

Cube::Cube() : Entity()
{
    std::string Path = File::CreatePath(File::GetExecutableDir() + "/Objects/Cube/CubeTest.obj");
    for (auto Comp : MeshComponent::FromObj(Path))
        AddComponent(Comp);
//    InputHandler::OnKeyPress(GLFW_KEY_W, InputAction::KEY_REPEATED, this, &Cube::MoveForward);
}

void Cube::Draw()
{
    Entity::Draw();
}

#endif OPENMINE_CUBE_H
