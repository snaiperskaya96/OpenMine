//
// Created by verrignij on 05/12/2017.
//

#ifndef OPENMINE_ENTITYPOOL_H
#define OPENMINE_ENTITYPOOL_H

#include <Entity/Entity.h>
#include <mutex>
#include "Pool.h"

class EntityPool : public Pool
{
public:
    static void Init()
    {
    }

    inline static void RegisterEntity(Entity* NewEntity)
    {
        EntityLock.lock();
        Entities.push_back(NewEntity);
        EntityLock.unlock();
    }

    inline static void Draw()
    {
    }

    inline static void Destroy()
    {
        for (auto Ent : Entities) {
            delete Ent;
        }
    }
protected:
    static std::vector<Entity*> Entities;
    static std::mutex EntityLock;
};

#endif //OPENMINE_ENTITYPOOL_H
