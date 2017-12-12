//
// Created by verrignij on 07/12/2017.
//

#ifndef OPENMINE_MESHCOMPONENT_H
#define OPENMINE_MESHCOMPONENT_H

#include "glad/glad.h"
#include <utility>
#include <vector>
#include "glm/detail/type_mat4x4.hpp"
#include "Component.h"
#include <string>

class MeshComponent : public Component
{
public:
    MeshComponent();
    void Init() override;
    void Draw() override;
public:
    static std::vector<MeshComponent*> FromObj(std::string& ObjPath);
    inline void SetVerticles(std::vector<GLfloat> NewVerticles) { Verticles = (NewVerticles); }
    inline void SetIndices(std::vector<GLuint> NewIndices) { Indices = (NewIndices); }
protected:
    glm::mat4 ModelMatrix;
    std::vector<GLfloat> Verticles;
    std::vector<GLuint> Indices;
    std::vector<GLfloat> UVs;
    std::vector<class Texture*> Textures;
    class Shader* EntityShader;
    GLint MvpUniform;
    GLint CoordAttrib;
    GLint UvAttrib;
    GLint TextureUniform;
    GLuint Vao;
    GLuint VertexVbo;
    GLuint ElementVbo;
    GLuint UvVbo;
};


#endif //OPENMINE_MESHCOMPONENT_H
