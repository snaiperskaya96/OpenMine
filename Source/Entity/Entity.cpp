//
// Created by verrignij on 05/12/2017.
//

#include "Entity.h"
#include <Pool/EntityPool.h>
#include "Camera/Camera.h"

void Entity::Draw()
{
    EntityShader->Use();
    Textures[0]->Bind(TextureUniform);

	glm::mat4 MvpMat = Camera::ProjectionMatrix * Camera::ViewMatrix * ModelMatrix;

    glUniformMatrix4fv(MvpUniform, 1, GL_FALSE, &MvpMat[0][0]);

    glDrawArrays(GL_LINES, 0, (GLsizei) Verticles.size() / 3);
}

void Entity::Begin()
{
    HasBegun = true;
}

void Entity::Initialise()
{
    CoordAttrib = glGetAttribLocation(EntityShader->GetProgramId(), "Coordinates");
    UvAttrib = glGetAttribLocation(EntityShader->GetProgramId(), "Uv");
    MvpUniform = glGetUniformLocation(EntityShader->GetProgramId(), "Mvp");
    TextureUniform = glGetUniformLocation(EntityShader->GetProgramId(), "Texture");

    glGenBuffers(1, &VertexVbo);
    glBindBuffer(GL_ARRAY_BUFFER, VertexVbo);
    glBufferData(GL_ARRAY_BUFFER, Verticles.size(), &Verticles[0], GL_STATIC_DRAW);

    glGenBuffers(1, &UvVbo);
    glBindBuffer(GL_ARRAY_BUFFER, UvVbo);
    glBufferData(GL_ARRAY_BUFFER, UVs.size(), &UVs[0], GL_STATIC_DRAW);

    EntityPool::RegisterEntity(this);
}

void Entity::BindBuffersToVao()
{
    glBindBuffer(GL_ARRAY_BUFFER, VertexVbo);
    glVertexAttribPointer(CoordAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glEnableVertexAttribArray(CoordAttrib);

    glBindBuffer(GL_ARRAY_BUFFER, UvVbo);
    glVertexAttribPointer(UvAttrib, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glEnableVertexAttribArray(UvAttrib);
}

Entity::Entity()
{
    EntityShader = nullptr;
    ModelMatrix = glm::mat4(1.f);
}
