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
    static void Init()
    {
    }

    inline static void RegisterEntity(Entity* NewEntity)
    {
        Entities.push_back(NewEntity);
    }

    inline static void Draw()
    {
        for (auto Ent : Entities) {
            if (!Ent->HasBegun) {
                Ent->Begin();
            }
            Ent->Draw();
        }
    }

    inline static void Destroy()
    {
        for (auto Ent : Entities) {
            delete Ent;
        }
    }
protected:
    static std::vector<Entity*> Entities;
};

#endif //OPENMINE_ENTITYPOOL_H
