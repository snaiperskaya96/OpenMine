#ifndef OPENMINE_CUBE_H
#define OPENMINE_CUBE_H

#include <Utils/FileSystem/File.h>
#include <Component/MeshComponent.h>
#include "Entity.h"

class Cube : public Entity
{
public:
    Cube();
};

Cube::Cube() : Entity()
{
    std::string Path = File::CreatePath(File::GetExecutableDir() + "/Objects/Cube/TexturedCube.obj");
    for (auto Comp : MeshComponent::FromObj(Path))
        AddComponent(Comp);
}

#endif OPENMINE_CUBE_H
