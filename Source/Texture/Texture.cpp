//
// Created by snaiperskaya on 03/12/17.
//

//#include <png.h>
#define STB_IMAGE_IMPLEMENTATION
#include <cstring>
#include <iostream>
#include <glad/glad.h>
#include "stb_image.h"
#include "Texture.h"

Texture *Texture::FromName(std::string Name)
{
#if 0
    png_image Image = {};

    memset(&Image, 0, (sizeof Image));
    Image.version = PNG_IMAGE_VERSION;

    if (png_image_begin_read_from_file(&Image, ("Textures/" + Name).c_str()) != 0) {
        png_bytep Buffer;
        Image.format = PNG_FORMAT_RGBA;
        Buffer = (png_bytep) malloc(PNG_IMAGE_SIZE(Image));
        if (Buffer != nullptr && png_image_finish_read(&Image, nullptr /*background*/, Buffer, 0/*row_stride*/, nullptr /*colormap*/) != 0) {
            auto T = new Texture(Buffer);
            return T;
        }
    }
#endif
    int Width, Height, Comp;
    unsigned char* Image = stbi_load(("Textures/" + Name).c_str(), &Width, &Height, &Comp, STBI_rgb);
    auto T = new Texture(Image);
    stbi_image_free(Image);
    return T;

    return nullptr;
}

Texture::Texture(unsigned char *Buffer)
{
    RawBuffer = Buffer;
    glGenTextures(1, &TextureId);
    glBindTexture(GL_TEXTURE_2D, TextureId);

    glTexImage2D(GL_TEXTURE, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, RawBuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureId);
    glUniform1i(TextureId, 0);
}
