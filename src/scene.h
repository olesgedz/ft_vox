#pragma once
#include "Entity.h"
#include <vector>

struct point_light
{
	glm::vec3	position;
	glm::vec3	color;
};

class Scene
{
public:
	std::vector<Entity*>		ents;
	std::vector<point_light>	point_lights;
public:
	void	add_entity(Entity* ent);
	void	add_light_source(glm::vec3 l_pos, glm::vec3 color);
};