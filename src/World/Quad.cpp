//
// Created by Jeromy Black on 12/25/20.
//

#include "Quad.h"
#include "glm/glm.hpp"
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
Quad::Quad(QuadType type, Mesh * mesh)
{
	switch (type)
	{
		case FRONT:
			for(vec3 &i : vFront)
				mesh->vertices.push_back(i);
			break;
		case BACK:
			for(glm::vec3 &i : vBack)
				mesh->vertices.push_back(i);
			break;
		case LEFT:
			for(glm::vec3 &i : vLeft)
				mesh->vertices.push_back(i);
			break;
		case RIGHT:
			for(glm::vec3 &i : vRight)
				mesh->vertices.push_back(i);
			break;
		case TOP:
			for(glm::vec3 &i : vTop)
				mesh->vertices.push_back(i);
			break;
		case BOTTOM:
			for(glm::vec3 &i : vBottom)
				mesh->vertices.push_back(i);
			break;
		default:
			break;
	}
}

unsigned int Quad::m_indices[6] = {
		0,  1,  3,
		1,  2,  3
};