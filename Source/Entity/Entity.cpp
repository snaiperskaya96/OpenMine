//
// Created by verrignij on 05/12/2017.
//

#include "Entity.h"
#include "Component/Component.h"
#include <Pool/EntityPool.h>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>

void Entity::Draw()
{
    if (!Visible) return;
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

void Entity::SetHidden(bool IsHidden)
{
    Visible = !IsHidden;
}

Transform Entity::GetRelativeTransform()
{
    Transform T{};
    glm::vec3 Skew{};
    glm::vec4 Perspective{};
    glm::decompose(ModelMatrix, T.Scale, T.Rotation, T.Translation, Skew, Perspective);
    return T;
}

glm::vec3 Entity::GetRelativeLocation()
{
    return GetRelativeTransform().Translation;
}
