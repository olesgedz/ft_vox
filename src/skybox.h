#pragma once
#include <vector>
#include <string>

class Skybox
{
public:
	unsigned char* text_data;
	unsigned int	vbo;
	unsigned int	vao;
	unsigned int	texture;
	int				shader_id;
public:
	void	init(std::vector<std::string> faces);
	void	set_shader(const char* vPath, const char* fpath);
};