//
// Created by snaiperskaya on 03/12/17.
//

#ifndef OPENMINE_SHADER_H
#define OPENMINE_SHADER_H

#include <utility>
#include <vector>
#include <string>
#include <map>
#include <glad/glad.h>

enum class ShaderType : int
{
    Vertex,
    Fragment,
};

struct ShaderFile
{
    ShaderFile(std::string Name, ShaderType Type) : Name(std::move(Name)), Type(Type), ShaderId(0) {}

    std::string GetType()
    {
        switch (Type) {
            case ShaderType::Vertex:
                return "Vertex";
            case ShaderType::Fragment:
                return "Fragment";
        }
    }

    GLuint GetGlType()
    {
        switch (Type) {
            case ShaderType::Vertex:
                return GL_VERTEX_SHADER;
            case ShaderType::Fragment:
                return GL_FRAGMENT_SHADER;
        }
    }

    std::string GetPath()
    {
        return "Shaders/" + GetType() + "/" + Name + ".glsl";
    }

    std::string Name;
    ShaderType Type;
    GLuint ShaderId;
};

class Shader
{
public:
    explicit Shader(std::vector<ShaderFile> ShaderFiles);
    void AddShader(ShaderFile SFile);
    void Link();
    void Use();
    void SetUniform(std::string UniformName, int UniformValue);
    GLuint GetProgramId() const { return ProgramId; }
protected:
    std::string GetShaderText(ShaderFile& SFile);
    GLint GetUniformLocation(std::string& UniformName);
protected:
    GLuint ProgramId;
    std::vector<ShaderFile> ShaderList;
    std::map<std::string, GLint> UniformLocations;
};


#endif //OPENMINE_SHADER_H
