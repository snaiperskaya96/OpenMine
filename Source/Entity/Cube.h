#ifndef OPENMINE_CUBE_H
#define OPENMINE_CUBE_H

#include <Utils/FileSystem/File.h>
#include <Component/MeshComponent.h>
#include <Handler/Input/InputHandler.h>
#include "Entity.h"

class Chunk;

class Cube : public Entity
{
public:
    inline Cube()
    {
        std::string Path = File::CreatePath(File::GetExecutableDir() + "/Objects/Cube/CubeTest.obj");
        for (auto Comp : MeshComponent::FromObj(Path))
            AddComponent(Comp);
    }

    inline void Draw() override
    {
        Entity::Draw();

    }

    inline void SetChunk(Chunk* Parent) { OwningChunk = Parent; }
    inline Chunk* GetChunk() { return OwningChunk; }
protected:
    Chunk* OwningChunk;
};

#endif OPENMINE_CUBE_H
