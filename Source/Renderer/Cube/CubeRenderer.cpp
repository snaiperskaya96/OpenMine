//
// Created by verrignij on 13/12/2017.
//

#include <Utils/FileSystem/File.h>
#include <Shader/Shader.h>
#include <Camera/Camera.h>
#include "Cache/ObjLoaderCache.h"
#include "Renderer/Cube/CubeRenderer.h"

void CubeRenderer::Init()
{
	Renderer::Init();
    std::string ObjPath = File::CreatePath(File::GetExecutableDir() + "Objects/Cube/TexturedCube.obj");
    ObjLoader* Loader = ObjLoaderCache::Get(ObjPath);

    if (!Loader) {
        if (!File::Exists(ObjPath)) {
            std::cout << "MeshComponent::FromObj: Invalid obj provided (" << ObjPath << ")";
            return;
        }

        Loader = new ObjLoader();
        Loader->LoadFile(ObjPath);
        ObjLoaderCache::Add(ObjPath, Loader);
    }

    BindVao();

    glGenBuffers(1, &ModelMatricesVbo);

    glGenBuffers(1, &VerticlesVbo);
    glBindBuffer(GL_ARRAY_BUFFER, VerticlesVbo);
    glBufferData(GL_ARRAY_BUFFER, Loader->LoadedVertices.size() * sizeof(float) * 8, &Loader->LoadedVertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &IndicesEbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Loader->LoadedIndices.size() * sizeof(GLuint), &Loader->LoadedIndices[0], GL_STATIC_DRAW);

    CubeShader = new Shader({
            {"cube", ShaderType::Vertex},
            {"cube", ShaderType::Fragment},
    });

    NumberOfIndices = Loader->LoadedIndices.size();

    CubeShader->Use();
    MvpUniformLocation = glGetUniformLocation(CubeShader->GetProgramId(), "Mvp");
    VertexLocation = glGetAttribLocation(CubeShader->GetProgramId(), "VertexPosition");
    ModelMatrixLocation = glGetAttribLocation(CubeShader->GetProgramId(), "ModelMatrix");

    glBindBuffer(GL_ARRAY_BUFFER, VerticlesVbo);
    glEnableVertexAttribArray((GLuint)VertexLocation);
    glVertexAttribPointer((GLuint)VertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*) 0);

    glBindBuffer(GL_ARRAY_BUFFER, ModelMatricesVbo);
    glEnableVertexAttribArray((GLuint)ModelMatrixLocation);
    for( int c = 0; c < 4; ++c )
    {
        glEnableVertexAttribArray((GLuint)ModelMatrixLocation + c);
        glVertexAttribPointer( (GLuint)ModelMatrixLocation + c, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4 * 4, (void*) (0 + c * sizeof(float) * 4));
        glVertexAttribDivisor( (GLuint)ModelMatrixLocation + c, 1 ); //is it instanced?
    }

    UnbindVao();
}

int CubeRenderer::AddCube(glm::mat4 ModelMatrix)
{
    CubeModelMatrices.push_back(ModelMatrix);
    return ModelMatricesIndex++;
}

void CubeRenderer::RemoveCube(int Index)
{
    CubeModelMatrices.erase(CubeModelMatrices.begin() + Index);
}

void CubeRenderer::Draw()
{
    Renderer::Draw();
    glm::mat4 MvpMat = Camera::ProjectionMatrix * Camera::ViewMatrix;

    CubeShader->Use();

    BindVao();
    glUniformMatrix4fv(MvpUniformLocation, 1, GL_FALSE, &MvpMat[0][0]);

    glBindBuffer( GL_ARRAY_BUFFER, ModelMatricesVbo);
    glBufferData( GL_ARRAY_BUFFER, sizeof(float) * 4 * 4 * CubeModelMatrices.size(), &CubeModelMatrices[0][0][0], GL_DYNAMIC_DRAW );
    //glBindBuffer(GL_ARRAY_BUFFER, VerticlesVbo);
//    glDrawArrays(GL_TRIANGLES, 0, 36 * CubeModelMatrices.size());
    //glDrawElements( GL_TRIANGLES, NumberOfIndices, GL_UNSIGNED_INT, 0 ); //two triangles per face, that is 6 * 6 = 36 vertices
    glDrawElementsInstanced( GL_TRIANGLES, NumberOfIndices, GL_UNSIGNED_INT, 0, (GLsizei) CubeModelMatrices.size());
    UnbindVao();
}

void CubeRenderer::UpdateModelMatrix(int Index, glm::mat4 NewMatrix)
{
    CubeModelMatrices.at(Index) = NewMatrix;
}
