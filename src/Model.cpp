#include "Model.h"
#include "glad.h"
#include "stb_image.h"
#include "Shader.h"
#include <iostream>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBuffersLayout.h"


#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>

//int Model::load_obj()
//{
//
//	return 0;
//}

//void Model::upload()
//{
//
//	if (this->vertices.size() > 0) {
//		glGenBuffers(1, &this->vbo_vertices);
//		glGenVertexArrays(1, &this->voa);
//		glBindVertexArray(this->voa);
//		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_vertices);
//		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices.data()[0]), vertices.data(), GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(0);
//		glCheckError();
//	}
//
//	if (normals.size() > 0)
//	{
//		glGenBuffers(1, &vbo_normals);
//		glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
//		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]),
//					 normals.data(), GL_STATIC_DRAW);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(1);
//	}
//	if (uvs.size() > 0)
//	{
//		if (textureExists)
//			textureExists = 1;
//		glGenBuffers(1, &vbo_uvs);
//		glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
//		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(uvs[0]),
//					 uvs.data(), GL_STATIC_DRAW);
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(2);
//	}
//	else
//	{
//		textureExists = 0;
//	}
//
//	if (this->vertexIndices.size() > 0)
//	{
//		glGenBuffers(1, &this->ebo);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->vertexIndices.size() * sizeof(this->vertexIndices[0]),
//					 this->vertexIndices.data(), GL_STATIC_DRAW);
//	}
//
//
//
//
//}
//
//void Model::set_shader(const char *vPath, const char* fSPath)
//{
//	create_shader(&shader_id, vPath, fSPath);
//}
//
//void Model:: load_texture(const char* path)
//{
//	int nrChannels;
//
//	text_data = stbi_load(path, &text_width, &text_height, &nrChannels, 0);
//	if (!text_data)
//		std::cout << "can't load texture file" << std::endl;
//	bind_texture();
//}
//void Model::draw()
//{
//
//}
//void Model::bind_texture()
//{
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, text_width, text_height, 0, GL_RGB, GL_UNSIGNED_BYTE, text_data);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	stbi_image_free(text_data);
//}
Model::~Model()
{
	meshes.clear();
}