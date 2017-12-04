//
// Created by snaiperskaya on 03/12/17.
//

#ifndef OPENMINE_TEXTURE_H
#define OPENMINE_TEXTURE_H

#include <string>
#include <GL/gl.h>

class Texture
{
public:
    Texture(unsigned char* Buffer);
    static Texture* FromName(std::string Name);

    void Bind(GLuint UniformId);

protected:
    unsigned char* RawBuffer;
    GLuint TextureId;
};


#endif //OPENMINE_TEXTURE_H
