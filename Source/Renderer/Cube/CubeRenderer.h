//
// Created by verrignij on 13/12/2017.
//

#ifndef OPENMINE_CUBERENDERER_H
#define OPENMINE_CUBERENDERER_H

#include <Renderer/Renderer.h>
#include <vector>
#include <glm/detail/type_mat4x4.hpp>
#include <mutex>


struct CubeModelMatrix {
    glm::mat4 Coords;
    int Index;
};

/**
 * Here we try to have only one VBO
 * for the verticles while having
 */

class CubeRenderer : public Renderer<CubeRenderer>
{
public:
    int AddCube(glm::mat4 ModelMatrix);
    void UpdateModelMatrix(int Index, glm::mat4 NewMatrix);
    void RemoveCube(int Index);

    void Draw() override;
protected:
    void Init() override;
    std::vector<CubeModelMatrix>::iterator GetIteratorAtIndex(int Index);
protected:
    std::mutex ModelMatricesMutex;
    class Shader* CubeShader;
    int ModelMatricesIndex = 0;
    GLuint VerticlesVbo = 0;
    GLuint IndicesEbo = 0;
    GLuint ModelMatricesVbo = 0;
    GLuint ProgramId = 0;
    //std::vector<glm::mat4> CubeModelMatrices;

    std::vector<CubeModelMatrix> CubeModelMatrices;
    // We use this so we don't block the drawing queue but it also means we don't render stuff straight away
    // will see if it works
    std::vector<CubeModelMatrix> TemporaryNewModelMatrices;
    std::vector<std::vector<CubeModelMatrix>::iterator> TemporaryRemovedModelMatrices;
    std::vector<CubeModelMatrix> TemporaryModifiedModelMatrices;

    GLint VertexLocation;
    GLint ModelMatrixLocation;
    GLint MvpUniformLocation;
    int NumberOfIndices;
};


#endif //OPENMINE_CUBERENDERER_H
