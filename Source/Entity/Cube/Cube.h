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

    void SetHidden(bool IsHidden) override
    {
        bool OldValue = Visible;
        Entity::SetHidden(IsHidden);
        if (Visible == OldValue) return;
        if (Visible) {
            RendererId = CubeRenderer::GetInstance()->AddCube(ModelMatrix);
        } else {
            CubeRenderer::GetInstance()->RemoveCube(RendererId);
        }
    }

protected:
    Chunk* OwningChunk;
    int RendererId;
};

#endif // OPENMINE_CUBE_H
