#include "entity.h"
#include "glm/glm.hpp"
int  Entity::idNumber = 0;
Entity::Entity()
{
	move_to(0.0f, 0.0f, 0.0f);
	scale(1.0f, 1.0f, 1.0f);
	set_color(1.0f, 1.0f, 1.0f);
 	set_offset(vec3(0,0,0));
	ID = idNumber;
	idNumber++;
}

void	Entity::update()
{

}
void  Entity::set_offset(vec3 offset)
{
	positionOffset = offset;
}
void Entity::set_model(Model *model)
{
	mod = model;
}

void Entity::move(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
}

void Entity::move_to(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Entity::rotate(float x, float y, float z)
{
	angle.x += x;
	angle.y += y;
	angle.z += z;
}

void Entity::rotate_to(float x, float y, float z)
{
	angle.x = x;
	angle.y = y;
	angle.z = z;
}

void Entity::scale(float x, float y, float z)
{
	e_scale.x = x;
	e_scale.y = y;
	e_scale.z = z;
}

void Entity::set_color(float r, float g, float b)
{
    color.x = r;
    color.y = g;
    color.z = b;
}

void Entity::set_parent(Entity *ent)
{
	parent = ent;
	ent->childrens.push_back(this);
}

