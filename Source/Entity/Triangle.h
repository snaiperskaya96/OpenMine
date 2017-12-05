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
          //  -0.666667f, -0.666667f, -0.000000f,
            //1.333333f, -0.666667f, -0.000000f,
            //-0.666667f, 1.333333f, 0.000000f,

            -1.f, -1.f, .75f,
            0.f, 1.f, .75f,
            1.f, -1.f, .75f
    };

    UVs = {
            0.0f, 0.5f,
            0.500000f, 0.0f,
            0.5f, 1.0f,
    };

    Textures.push_back(Texture::FromName("layout.png"));

    EntityShader = new Shader(
            {
                    {"test", ShaderType::Vertex},
                    {"test", ShaderType::Fragment},
            }
    );
}

#endif //OPENMINE_TRIANGLE_H
