#ifndef OPENMINE_CUBE_H
#define OPENMINE_CUBE_H

#include <Utils/FileSystem/File.h>
#include <Handler/Input/InputHandler.h>
#include "Entity/Entity.h"
#include "Renderer/Cube/CubeRenderer.h"

class Chunk;

class Cube : public Entity
{
public:
    inline Cube()
    {
        RendererId = CubeRenderer::GetInstance()->AddCube(ModelMatrix);
/*
        std::string Path = File::CreatePath(File::GetExecutableDir() + "/Objects/Cube/CubeTest.obj");
        for (auto Comp : MeshComponent::FromObj(Path)) {
            ((MeshComponent*)Comp)->SetIndices(
                    {
                            0, 1, 2,
                            2, 3, 0,

                            4, 5, 6,
                            6, 7, 4,

                            8, 9, 10,
                            10, 11, 8,

                            12, 13, 14,
                            14, 15, 12,

                            16, 17, 18,
                            18, 19, 16,

                            20, 21, 22,
                            22, 23, 20
                    }
            );

            ((MeshComponent*)Comp)->SetVerticles(
                    {
                            1.f, 0.f, 0.f,
                            0.f, 0.f, 0.f,
                            0.f, 1.f, 0.f,
                            1.f, 1.f, 0.f,

                            //Front
                            0.f, 0.f, 1.f,
                            1.f, 0.f, 1.f,
                            1.f, 1.f, 1.f,
                            0.f, 1.f, 1.f,

                            //Right
                            1.f, 0.f, 1.f,
                            1.f, 0.f, 0.f,
                            1.f, 1.f, 0.f,
                            1.f, 1.f, 1.f,

                            //Left
                            0.f, 0.f, 0.f,
                            0.f, 0.f, 1.f,
                            0.f, 1.f, 1.f,
                            0.f, 1.f, 0.f,

                            //Top
                            0.f, 1.f, 1.f,
                            1.f, 1.f, 1.f,
                            1.f, 1.f, 0.f,
                            0.f, 1.f, 0.f,

                            //Bottom
                            0.f, 0.f, 0.f,
                            1.f, 0.f, 0.f,
                            1.f, 0.f, 1.f,
                            0.f, 0.f, 1.f
                    }
            );
            AddComponent(Comp);
        }
        */
    }

    inline void Draw() override
    {
        Entity::Draw();
    }

    inline void SetChunk(Chunk* Parent) { OwningChunk = Parent; }
    inline Chunk* GetChunk() { return OwningChunk; }

    void SetRelativeLocation(glm::vec3 Location) override
    {
        Entity::SetRelativeLocation(Location);
        CubeRenderer::GetInstance()->UpdateModelMatrix(RendererId, ModelMatrix);
    }

protected:
    Chunk* OwningChunk;
    int RendererId;
};

#endif OPENMINE_CUBE_H
