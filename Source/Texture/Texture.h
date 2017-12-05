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
    explicit Texture(int Width, int Height, int Channels, unsigned char *Buffer);
    static Texture* FromName(std::string Name);

    void Bind(GLuint UniformId);

    inline GLuint GetId() { return TextureId; }

protected:
    unsigned char* RawBuffer;
    GLuint TextureId;
    int Width;
    int Height;
    int Channels;
};


#endif //OPENMINE_TEXTURE_H
