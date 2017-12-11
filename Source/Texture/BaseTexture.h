//
// Created by verrignij on 08/12/2017.
//

#ifndef OPENMINE_BASETEXTURE_H
#define OPENMINE_BASETEXTURE_H


#include <glad/glad.h>
#include "Texture.h"

class BaseTexture : public Texture
{
public:
    BaseTexture();
};

BaseTexture::BaseTexture()
{
    Width = Height = 128;
    Channels = 3;
    RawBuffer = (unsigned char*) malloc((size_t) Width * Height * 3);
    memset(RawBuffer, 1, (size_t) Width * Height * 3);

    glGenTextures(1, &TextureId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, RawBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


#endif //OPENMINE_BASETEXTURE_H
