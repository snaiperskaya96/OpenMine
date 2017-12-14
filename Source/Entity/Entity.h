//
// Created by verrignij on 05/12/2017.
//

#ifndef OPENMINE_ENTITY_H
#define OPENMINE_ENTITY_H

#include <glad/glad.h>
#include <vector>
#include <Texture/Texture.h>
#include <Shader/Shader.h>
#include <glm/detail/type_mat4x4.hpp>
#include <Math/Math.h>

class Entity
{
    friend class EntityPool;
public:
    Entity();
    virtual void Begin();
    virtual void Draw();

    virtual void SetRelativeLocation(glm::vec3 Location);
    virtual Transform GetRelativeTransform();
    virtual glm::vec3 GetRelativeLocation();

    void AddComponent(class Component *Comp);
    virtual void SetHidden(bool IsHidden);
    inline bool IsVisible() { return Visible; }

    glm::mat4 GetModelMatrix();
protected:
    std::vector<class Component*> Components;
    glm::mat4 ModelMatrix;
    bool HasBegun = false;
    bool Visible = true;

};


#endif //OPENMINE_ENTITY_H
