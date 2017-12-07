//
// Created by verrignij on 05/12/2017.
//

#ifndef OPENMINE_TRIANGLE_H
#define OPENMINE_TRIANGLE_H

#include "Entity.h"

class Triangle : public Entity
{
public:
    Triangle();
};

Triangle::Triangle() : Entity()
{
    Verticles = {
            0, 0, 0,
            1, 1, 1,
            1, 0, 1
    };

    Indices = {
            0, 1, 2
    };

    UVs = {
            0.0f, 0.5f,
            0.500000f, 0.0f,
            0.5f, 1.0f,
    };

    Textures.push_back(Texture::FromName("layout.png"));

    EntityShader = new Shader(
            {
                    {"base-texture", ShaderType::Vertex},
                    {"base-texture", ShaderType::Fragment},
            }
    );
}

#endif //OPENMINE_TRIANGLE_H
