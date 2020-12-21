#ifndef SHADERLOADER_HPP
#define SHADERLOADER_HPP
#include "vox.hpp"
#include <string>
namespace Shader
{
    GLuint loadShader(const std::string& vertexShaderFile,
                    const std::string& fragmentShaderFile);
}

#endif