//
// Created by snaiperskaya on 03/12/17.
//

#include <iostream>
#include "Shader.h"
#include "Utils/FileSystem/File.h"

Shader::Shader(std::vector<ShaderFile> ShaderFiles)
{
    ProgramId = glCreateProgram();
    for (auto& SFile : ShaderFiles) {
        AddShader(SFile);
    }
}

std::string Shader::GetShaderText(ShaderFile& SFile)
{
    std::string ShaderText = File::GetTextFromFile(SFile.GetPath());

    if (ShaderText.empty()) {
        std::cout << "Invalid shader file " << SFile.Name << " (" << SFile.GetPath() << ")" << std::endl;
        return "";
    }

    return ShaderText;
}

void Shader::AddShader(ShaderFile SFile)
{
    auto Text = GetShaderText(SFile);
    if (Text.empty()) return;

    SFile.ShaderId = glCreateShader(SFile.GetGlType());
    const char* T = Text.c_str();
    glShaderSource(SFile.ShaderId, 1, &T, nullptr);
    glCompileShader(SFile.ShaderId);

    GLint Compiled = 0;
    glGetShaderiv(SFile.ShaderId, GL_COMPILE_STATUS, &Compiled);
    if (Compiled == GL_FALSE) {
        GLint LogLength = 0;
        glGetShaderiv(SFile.ShaderId, GL_INFO_LOG_LENGTH, &LogLength);
        auto ErrorLog = new GLchar[LogLength];
        glGetShaderInfoLog(SFile.ShaderId, LogLength, &LogLength, &ErrorLog[0]);
        std::cout << "Shader linking error: " << &ErrorLog[0] << std::endl;
        delete[] ErrorLog;
        glDeleteShader(SFile.ShaderId);
    }

    ShaderList.push_back(SFile);
}

void Shader::Link()
{
    for (ShaderFile& SFile : ShaderList) {
        glAttachShader(ProgramId, SFile.ShaderId);
    }

    glLinkProgram(ProgramId);
    GLint Linked = 0;
    glGetProgramiv(ProgramId, GL_LINK_STATUS, &Linked);

    if (Linked == GL_FALSE) {
        GLint LogLength = 0;
        glGetProgramiv(ProgramId, GL_INFO_LOG_LENGTH, &LogLength);
        auto ErrorLog = new GLchar[LogLength];
        glGetProgramInfoLog(ProgramId, LogLength, &LogLength, &ErrorLog[0]);
        std::cout << "Program linking error: " << ErrorLog << std::endl;
        delete[] ErrorLog;
        glDeleteProgram(ProgramId);
    }
}

void Shader::Use()
{
    glUseProgram(ProgramId);
}

void Shader::SetUniform(std::string UniformName, int UniformValue)
{
    glUniform1i(GetUniformLocation(UniformName), UniformValue);
}

GLint Shader::GetUniformLocation(std::string& UniformName)
{
    auto UniformLocation = UniformLocations.find(UniformName);
    if (UniformLocation != UniformLocations.end()) {
        return UniformLocation->second;
    } else {
        GLint Location = glGetUniformLocation(ProgramId, UniformName.c_str());
        UniformLocations.insert(std::pair<std::string, GLint>(UniformName, Location));
        return Location;
    }
}