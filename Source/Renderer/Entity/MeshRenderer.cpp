//
// Created by verrignij on 12/12/2017.
//

#include "MeshRenderer.h"

void MeshRenderer::Draw()
{
    Renderer::Draw();
}

int MeshRenderer::AddMesh(class MeshComponent* NewEntity)
{
    VerticlesMutex.lock();
    int Index = VerticlesIndex++;

    VerticlesMutex.unlock();
    return Index;
}
