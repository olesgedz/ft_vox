#include "scene.h"

void	Scene::add_entity(Entity* ent)
{
	ents.push_back(ent);
}

void	Scene::add_light_source(glm::vec3 l_pos, glm::vec3 color)
{
	point_lights.push_back({ l_pos, color });
}
