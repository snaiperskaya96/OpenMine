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

class Entity
{
    friend class EntityPool;
public:
    Entity();
    void Begin();
    void Draw();

    void SetRelativeLocation(glm::vec3 Location);
    void AddComponent(class Component *Comp);

    glm::mat4 GetModelMatrix();
protected:
    std::vector<class Component*> Components;
    glm::mat4 ModelMatrix;
    bool HasBegun = false;

};


#endif //OPENMINE_ENTITY_H
