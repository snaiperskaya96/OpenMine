//
// Created by verrignij on 07/12/2017.
//

#include <Camera/Camera.h>
#include <Utils/FileSystem/File.h>
#include "Cache/ShaderCache.h"
#include "MeshComponent.h"
#include "Texture/Texture.h"
#include "Entity/Entity.h"
#include "Cache/ObjLoaderCache.h"

MeshComponent::MeshComponent()
{
    Textures.push_back(Texture::FromName("cube.png"));

    std::string ShaderName = "cube-shader";

    EntityShader = ShaderCache::Get(ShaderName);
    if (!EntityShader) {
        EntityShader = new Shader(
                {
                        {"base-texture", ShaderType::Vertex},
                        {"base-texture", ShaderType::Fragment},
                }
        );

        ShaderCache::Add(ShaderName, EntityShader);
    }
    ModelMatrix = glm::mat4(1.f);
}

std::vector<MeshComponent *> MeshComponent::FromObj(std::string& ObjPath)
{
    std::vector<MeshComponent*> Components;

    ObjLoader* Loader = ObjLoaderCache::Get(ObjPath);

    if (!Loader) {
        if (!File::Exists(ObjPath)) {
            std::cout << "MeshComponent::FromObj: Invalid obj provided (" << ObjPath << ")";
            return Components;
        }

        Loader = new ObjLoader();
        Loader->LoadFile(ObjPath);
        ObjLoaderCache::Add(ObjPath, Loader);
    }

    for (auto& Mesh : Loader->LoadedMeshes) {
        auto NewComponent = new MeshComponent();
        NewComponent->Indices = Mesh.Indices;

        for (auto& Vertex : Mesh.Vertices) {
            NewComponent->Verticles.push_back(Vertex.Position.X);
            NewComponent->Verticles.push_back(Vertex.Position.Y);
            NewComponent->Verticles.push_back(Vertex.Position.Z);
            NewComponent->UVs.push_back(Vertex.TextureCoordinate.X);
            NewComponent->UVs.push_back(Vertex.TextureCoordinate.Y);
        }

        Components.push_back(NewComponent);
    }

    return Components;
}

void MeshComponent::Init()
{
    Component::Init();

    EntityShader->Use();

    CoordAttrib = glGetAttribLocation(EntityShader->GetProgramId(), "Coordinates");
    UvAttrib = glGetAttribLocation(EntityShader->GetProgramId(), "Uv");
    MvpUniform = glGetUniformLocation(EntityShader->GetProgramId(), "Mvp");
    TextureUniform = glGetUniformLocation(EntityShader->GetProgramId(), "Texture");

    glGenVertexArrays(1, &Vao);
    glBindVertexArray(Vao);

    glGenBuffers(1, &VertexVbo);
    glBindBuffer(GL_ARRAY_BUFFER, VertexVbo);
    glBufferData(GL_ARRAY_BUFFER, Verticles.size() * sizeof(float), &Verticles[0], GL_STATIC_DRAW);

    if (!UVs.empty()) {
        glGenBuffers(1, &UvVbo);
        glBindBuffer(GL_ARRAY_BUFFER, UvVbo);
        glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(float), &UVs[0], GL_STATIC_DRAW);
    }

    if (!Indices.empty()) {
        glGenBuffers(1, &ElementVbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementVbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(GLuint), &Indices[0], GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, VertexVbo);
    glVertexAttribPointer((GLuint)CoordAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glEnableVertexAttribArray((GLuint)CoordAttrib);

    if (!UVs.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, UvVbo);
        glVertexAttribPointer((GLuint) UvAttrib, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);
        glEnableVertexAttribArray((GLuint) UvAttrib);
    }

    if (!Indices.empty()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementVbo);
    }

    UVs.clear();
    Verticles.clear();
}

void MeshComponent::Draw()
{
    Component::Draw();
    glBindVertexArray(Vao);

    Textures[0]->Bind((GLuint)TextureUniform);

    glm::mat4 MvpMat = Camera::ProjectionMatrix * Camera::ViewMatrix * ModelMatrix * Owner->GetModelMatrix();

    glUniformMatrix4fv(MvpUniform, 1, GL_FALSE, &MvpMat[0][0]);

    if (Indices.empty()) {
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)Verticles.size() / 3);
    } else {
        glDrawElements(GL_TRIANGLE_STRIP, (GLsizei)Indices.size(), GL_UNSIGNED_INT, nullptr);
    }

}
