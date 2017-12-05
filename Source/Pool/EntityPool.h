//
// Created by verrignij on 05/12/2017.
//

#ifndef OPENMINE_ENTITYPOOL_H
#define OPENMINE_ENTITYPOOL_H

#include <Entity/Entity.h>
#include "Pool.h"

class EntityPool : public Pool
{
public:
    inline static void Init()
    {
        GLuint Vao;
        glGenVertexArrays(1, &Vao);
        glBindVertexArray(Vao);

        Vaos.push_back(Vao);
    }

    inline static void RegisterEntity(Entity* NewEntity)
    {
        glBindVertexArray(Vaos[0]);
        NewEntity->BindBuffersToVao();
        Entities.push_back(NewEntity);
    }

    inline static void Draw()
    {
        glBindVertexArray(Vaos[0]);
        for (auto Ent : Entities) {
            if (Ent->HasBegun) {
                Ent->Draw();
            } else {
                Ent->Begin();
            }
        }
    }
protected:
    static std::vector<Entity*> Entities;
};

#endif //OPENMINE_ENTITYPOOL_H
