#pragma once
#ifndef SHADER_H
#define SHADER_H
// include glad to get all the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/gtx/string_cast.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
class Shader : public std::enable_shared_from_this<Shader>
{
public:
	// the program ID
	unsigned int ID;
	unsigned int Program;

	// constructor reads and builds the shader
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

	// use/activate the shader
	void use();

	// utility uniform functions
	void setBool(const std::string &name, bool value) const;

	void setInt(const std::string &name, int value) const;

	void setFloat(const std::string &name, float value) const;

	void setVec2(const std::string &name, const glm::vec2 &value) const;

	void setVec2(const std::string &name, float x, float y) const;

	void setVec3(const std::string &name, const glm::vec3 &value) const;

	void setVec3(const std::string &name, float x, float y, float z) const;

	// ------------------------------------------------------------------------
	void setVec4(const std::string &name, const glm::vec4 &value) const;

	void setVec4(const std::string &name, float x, float y, float z, float w);

	// ------------------------------------------------------------------------
	void setMat2(const std::string &name, const glm::mat2 &mat) const;

	// ------------------------------------------------------------------------
	void setMat3(const std::string &name, const glm::mat3 &mat) const;

	// ------------------------------------------------------------------------
	void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(GLuint shader, std::string type);
};

#endif