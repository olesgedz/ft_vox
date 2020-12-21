#pragma once
#include "Model.h"
#include <vector>
#include "glm/glm.hpp"
using namespace glm;
class Entity
{
public:
	Model	*mod;
	vec3	position;
	vec3	e_scale;
	vec3	angle;
	vec3    color;
	int 		ID;
	std::vector<Entity *> childrens;
	Entity*     parent;
	vec3 positionOffset;
public:
	Entity();
	void			set_model(Model *mod);
	void			move(float x, float y, float z);
	void			move_to(float x, float y, float z);
	void			rotate(float x, float y, float z);
	void			rotate_to(float x, float y, float z);
	void			scale(float x, float y, float z);
	virtual void	update();
    void            set_color(float r, float g, float b);
    void            set_parent(Entity* ent);
	void            set_offset(vec3 offset);
private:
	static int idNumber;
};
