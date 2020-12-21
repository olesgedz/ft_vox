#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "maths.h"

class Camera
{
public:
	vec3	pos;
	vec3	front;
	vec3	target;
	vec3	direction;
	vec3	right;
	vec3	up;
	mat4	view;
	float		speed;
	float		yaw;
	float		pitch;
public:
	Camera();
	void	update_free();
	void	update_follow(glm::vec3 targ);
private:

};
