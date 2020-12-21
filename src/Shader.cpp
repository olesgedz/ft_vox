#include "glad.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "shader.h"

static std::string load_shader(const char* filepath)
{
	std::ifstream data(filepath);
	std::string line;
	std::stringstream str;

	if (data.fail())
		std::cout << ".shader file not found" << std::endl;
	while (std::getline(data, line))
		str << line << '\n';
	return str.str();
}

static unsigned int compile_shader(unsigned int type, const std::string source)
{
	unsigned id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length + 1];
		glGetShaderInfoLog(id, length, &length, message);
		if (type == GL_VERTEX_SHADER)
			std::cout << "vertex "; 
		else
			std::cout << "fragment ";
		std::cout << "shader compilation failed" << std::endl;
		std::cout << message << std::endl;
		delete[](message);
		glDeleteShader(id);
		return 0;
	}
	return id;
}

int create_shader(int *program, const char *vertexPath, const char *fragmentPath)
{
	std::string vertexShader = load_shader(vertexPath);
	std::string fragmentShader = load_shader(fragmentPath);
	if (vertexShader.empty() || fragmentShader.empty())
	{
		*program = 0;
		return 0;
	}
	*program = glCreateProgram();
	unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShader);
	if (vs == 0 || fs == 0)
	{
		*program = 0;
		return 0;
	}
	glAttachShader(*program, vs);
	glAttachShader(*program, fs);
	glLinkProgram(*program);
	int result;
	glGetProgramiv(*program, GL_LINK_STATUS, &result);
	if (!result)
	{
		int length;
		glGetProgramiv(*program, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length + 1];
		glGetProgramInfoLog(*program, length, &length, message);
		std::cout << "link error" << std::endl;
		std::cout << message << std::endl;
		delete[](message);
	}
	glValidateProgram(*program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	return *program;
}
