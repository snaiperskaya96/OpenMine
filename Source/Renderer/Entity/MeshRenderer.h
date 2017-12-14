//
// Created by verrignij on 12/12/2017.
//

#ifndef OPENMINE_ENTITYRENDERER_H
#define OPENMINE_ENTITYRENDERER_H

#include <Renderer/Renderer.h>
#include <vector>
#include <glm/detail/type_mat.hpp>
#include <mutex>

class MeshRenderer : public Renderer<MeshRenderer>
{
public:
    int AddMesh(class MeshComponent* Mesh);
    void Draw() override;
protected:
    GLuint VerticlesVbo;
    GLuint ModelMatrixVbo;
    GLuint VerticlesEbo;
    int VerticlesIndex = -1;
    std::mutex VerticlesMutex;
    std::vector<glm::mat4> Verticles;
    std::vector<class Component*> Components;
};


#endif //OPENMINE_ENTITYRENDERER_H
