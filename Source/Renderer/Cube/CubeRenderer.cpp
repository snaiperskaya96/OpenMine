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
        glVertexAttribPointer( (GLuint)ModelMatrixLocation + c, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4 * 4 + sizeof(int), (void*) (0 + c * sizeof(float) * 4));
        glVertexAttribDivisor( (GLuint)ModelMatrixLocation + c, 1 ); //is it instanced?
    }

    UnbindVao();
}

int CubeRenderer::AddCube(glm::mat4 ModelMatrix)
{
    ModelMatricesMutex.lock();
    TemporaryNewModelMatrices.push_back({ModelMatrix, ModelMatricesIndex++});
//    CubeModelMatrices.push_back({ModelMatrix, ModelMatricesIndex++});
    ModelMatricesMutex.unlock();
    return ModelMatricesIndex;
}

std::vector<CubeModelMatrix>::iterator CubeRenderer::GetIteratorAtIndex(int Index)
{
    for (auto It = CubeModelMatrices.begin(); It < CubeModelMatrices.end(); ++It) {
        if (It.base()->Index == Index) {
            return It;
        }
    }
    return CubeModelMatrices.end();
}

void CubeRenderer::RemoveCube(int Index)
{
//    ModelMatricesMutex.lock();
    auto It = GetIteratorAtIndex(Index);
    if (It != CubeModelMatrices.end()) {
        TemporaryRemovedModelMatrices.push_back(It);
//        CubeModelMatrices.erase(It);
    }
//    ModelMatricesMutex.unlock();
}

void CubeRenderer::Draw()
{
    Renderer::Draw();

    if (TemporaryNewModelMatrices.size() > 50) {
        ModelMatricesMutex.lock();
        CubeModelMatrices.insert(CubeModelMatrices.end(), TemporaryNewModelMatrices.begin(), TemporaryNewModelMatrices.end());
        TemporaryNewModelMatrices.empty();
        ModelMatricesMutex.unlock();
    }

    glm::mat4 MvpMat = Camera::ProjectionMatrix * Camera::ViewMatrix;

    CubeShader->Use();

    BindVao();
    glUniformMatrix4fv(MvpUniformLocation, 1, GL_FALSE, &MvpMat[0][0]);

    glBindBuffer( GL_ARRAY_BUFFER, ModelMatricesVbo);

    ModelMatricesMutex.lock();
    glBufferData( GL_ARRAY_BUFFER, ((sizeof(float) * 4 * 4) +  (sizeof(int))) * CubeModelMatrices.size(), &CubeModelMatrices[0], GL_DYNAMIC_DRAW );
    glDrawElementsInstanced( GL_TRIANGLES, NumberOfIndices, GL_UNSIGNED_INT, 0, (GLsizei) CubeModelMatrices.size());
    ModelMatricesMutex.unlock();

    UnbindVao();
}

void CubeRenderer::UpdateModelMatrix(int Index, glm::mat4 NewMatrix)
{
    ModelMatricesMutex.lock();
    auto It = GetIteratorAtIndex(Index);
    if (It != CubeModelMatrices.end()) {
        CubeModelMatrix Mm = {NewMatrix, Index};
        TemporaryModifiedModelMatrices.push_back(Mm);
    //    It.base()->Coords = NewMatrix;
    }
    ModelMatricesMutex.unlock();
}
