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
    void Initialise();
    void SetRelativeLocation(glm::vec3 Location);
protected:
    void BindBuffersToVao();
protected:
    glm::mat4 ModelMatrix;
    std::vector<GLfloat> Verticles;
    std::vector<GLuint> Faces;
    std::vector<GLfloat> UVs;
    std::vector<Texture*> Textures;
    Shader* EntityShader;
    GLint MvpUniform;
    GLint CoordAttrib;
    GLint UvAttrib;
    GLint TextureUniform;
    GLuint VertexVbo;
    GLuint UvVbo;
    bool HasBegun = false;
};


#endif //OPENMINE_ENTITY_H
