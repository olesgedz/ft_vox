//
// Created by Jeromy Black on 12/25/20.
//

#include "Quad.h"
#include "glm/glm.hpp"
#include "Chunk.h"
static vec3 vFront [] ={
		vec3(0.5f,  0.5f,  0.0f),
		vec3(0.5f, -0.5f,  0.0f),
		vec3(-0.5f, -0.5f,  0.0f),   //FRONT
		vec3(-0.5f,  0.5f,  0.0f)
};
static vec3 vBack [] = {
		vec3(0.5f,  0.5f, -1.0f),
		vec3(0.5f, -0.5f, -1.0f), //BACK
		vec3(-0.5f, -0.5f, -1.0f),
		vec3(-0.5f,  0.5f, -1.0f)
};
static vec3 vTop [] = {
		vec3(-0.5f,  0.5f,  0.0f),
		vec3(-0.5f,  0.5f, -1.0f),    //TOP
		vec3(0.5f,  0.5f, -1.0f),
		vec3(0.5f,  0.5f,  0.0f)
};
static vec3 vBottom [] = {
		vec3(-0.5f, -0.5f,  0.0f),
		vec3(-0.5f, -0.5f, -1.0f),    //DOWN
		vec3(0.5f, -0.5f, -1.0f),
		vec3(0.5f, -0.5f,  0.0f)
};
static vec3 vRight [] = {
		vec3(0.5f,  0.5f,  0.0f),
		vec3(0.5f, -0.5f,  0.0f),    //RIGHT
		vec3(0.5f, -0.5f, -1.0f),
		vec3(0.5f,  0.5f, -1.0f)
};
static vec3 vLeft [] = {
		vec3(-0.5f, -0.5f, -1.0f),
		vec3(-0.5f,  0.5f, -1.0f),     //LEFT
		vec3(-0.5f,  0.5f,  0.0f),
		vec3(-0.5f, -0.5f,  0.0f)
};
Quad::Quad(QuadType type, Chunk * chunk, vec3 &pos)
{
//	for(vec3 i : vFront)
//		chunk->model.meshes[0].vertices.push_back(i);

	switch (type)
	{
		case FRONT:
			for(vec3 &i : vFront)
				chunk->model.meshes[0].vertices.push_back(i + pos);
			break;
		case BACK:
			for(glm::vec3 &i : vBack)
				chunk->model.meshes[0].vertices.push_back(i + pos);
			break;
		case LEFT:
			for(glm::vec3 &i : vLeft)
				chunk->model.meshes[0].vertices.push_back(i + pos);
			break;
		case RIGHT:
			for(glm::vec3 &i : vRight)
				chunk->model.meshes[0].vertices.push_back(i + pos);
			break;
		case TOP:
			for(glm::vec3 &i : vTop)
				chunk->model.meshes[0].vertices.push_back(i + pos);
			break;
		case BOTTOM:
			for(glm::vec3 &i : vBottom)
				chunk->model.meshes[0].vertices.push_back(i + pos);
			break;
		default:
			break;
	}
	for (auto index : Quad::m_indices)
		chunk->model.meshes[0].vertexIndices.push_back(index + chunk->n_vertices);
	chunk->n_vertices += 4;
}

unsigned int Quad::m_indices[6] = {
		0,  1,  3,
		1,  2,  3
};