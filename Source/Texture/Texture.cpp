//
// Created by snaiperskaya on 03/12/17.
//

#include <cstring>
#include <glad/glad.h>
#include <Utils/FileSystem/File.h>
#include <Utils/Thread/AsyncTask.h>
#include <Cache/TextureCache.h>
#include "stb_image.h"
#include "Texture.h"

Texture *Texture::FromName(std::string Name)
{
    auto CachedTexture = TextureCache::Get(Name);
    if (CachedTexture) {
        return CachedTexture;
    }
    stbi_set_flip_vertically_on_load(true);
    std::string Path = File::GetExecutableDir() + "Textures" + Separator + Name;
    int Width, Height, Comp = 0;
    stbi_info(Path.c_str(), &Width, &Height, &Comp);
    unsigned char* Image = stbi_load(Path.c_str(), &Width, &Height, &Comp, 3);
    auto T = new Texture(Width, Height, Comp, Image);
    T->Width = Width;
    T->Height = Height;
    T->Channels = Comp;
    TextureCache::Add(Name, T);
    return T;
}

Texture::Texture(int Width, int Height, int Channels, unsigned char *Buffer)
        : Width(Width), Height(Height), Channels(Channels), RawBuffer(Buffer)
{
    RawBuffer = Buffer;
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

void Texture::Bind(GLuint UniformId)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureId);
    glUniform1i(UniformId, 0);
}
