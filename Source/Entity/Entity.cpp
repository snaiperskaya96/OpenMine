//
// Created by verrignij on 05/12/2017.
//

#include "Entity.h"
#include "GLFW/glfw3.h"
#include <Pool/EntityPool.h>
#include <OpenMine/OpenMine.h>
#include <glm/ext.hpp>
#include "Camera/Camera.h"

void Entity::Draw()
{
    EntityShader->Use();
    Textures[0]->Bind(TextureUniform);

	glm::mat4 MvpMat = Camera::ProjectionMatrix * Camera::ViewMatrix * ModelMatrix;

    glUniformMatrix4fv(MvpUniform, 1, GL_FALSE, &MvpMat[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    if(glfwGetKey(OpenMine::GetWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3{0.f, 0.f, 0.1f});
    }
    if(glfwGetKey(OpenMine::GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3{0.f, 0.f, -0.1f});
    }
}

void Entity::Begin()
{
    HasBegun = true;
}

void Entity::Initialise()
{
    EntityShader->Use();

    CoordAttrib = glGetAttribLocation(EntityShader->GetProgramId(), "Coordinates");
    UvAttrib = glGetAttribLocation(EntityShader->GetProgramId(), "Uv");
    MvpUniform = glGetUniformLocation(EntityShader->GetProgramId(), "Mvp");
    TextureUniform = glGetUniformLocation(EntityShader->GetProgramId(), "Texture");

    glGenBuffers(1, &VertexVbo);
    glBindBuffer(GL_ARRAY_BUFFER, VertexVbo);
    // Remember to use the actual size in bytes
    glBufferData(GL_ARRAY_BUFFER, Verticles.size() * sizeof(float), &Verticles[0], GL_STATIC_DRAW);

    glGenBuffers(1, &UvVbo);
    glBindBuffer(GL_ARRAY_BUFFER, UvVbo);
    glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(float), &UVs[0], GL_STATIC_DRAW);

    EntityPool::RegisterEntity(this);
}

void Entity::BindBuffersToVao()
{
    glBindBuffer(GL_ARRAY_BUFFER, VertexVbo);
    glVertexAttribPointer((GLuint)CoordAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glEnableVertexAttribArray((GLuint)CoordAttrib);

    glBindBuffer(GL_ARRAY_BUFFER, UvVbo);
    glVertexAttribPointer((GLuint)UvAttrib, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glEnableVertexAttribArray((GLuint)UvAttrib);
}

Entity::Entity()
{
    EntityShader = nullptr;
    ModelMatrix = glm::mat4(1.f);
}

void Entity::SetRelativeLocation(glm::vec3 Location)
{
    ModelMatrix = glm::translate(glm::mat4(1.f), Location);
}