//
// Created by verrignij on 05/12/2017.
//

#include "Entity.h"
#include "Component/Component.h"
#include <Pool/EntityPool.h>
#include <glm/ext.hpp>

void Entity::Draw()
{
    for (auto Comp : Components) {
        Comp->Draw();
    }
}

void Entity::Begin()
{
    HasBegun = true;
}

Entity::Entity()
{
    ModelMatrix = glm::mat4(1.f);
    EntityPool::RegisterEntity(this);
}

void Entity::SetRelativeLocation(glm::vec3 Location)
{
    ModelMatrix = glm::translate(glm::mat4(1.f), Location);
}

glm::mat4 Entity::GetModelMatrix()
{
    return ModelMatrix;
}

void Entity::AddComponent(Component* Comp)
{
    Comp->SetOwner(this);
    Comp->Init();
    Components.push_back(Comp);
}