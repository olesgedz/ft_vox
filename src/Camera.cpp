#include "camera.h"
#include <iostream>
Camera::Camera()
{
	pos = vec3(-1.0f, 0.0f, 5.0f);
	front = vec3(0.0f, 0.0f, -1.0f);
	target = vec3(0.0f, 0.0f, 0.0f);
	direction = normalize(pos - target);
	vec3 temp_up = vec3(0.0f, 1.0f, 0.0f);
	right = normalize(cross(temp_up, direction));
	up = cross(direction,right);
    view = look_at(pos, pos + front, up);
	yaw = -90.0f;
	pitch = 0.0f;
	speed = 0.5f;
}

void Camera::update_free()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = normalize(front);
	view = look_at(pos, pos + front, up);
}

//void Camera::update_follow(glm::vec3 targ)
//{
//	pos.x = targ.x - cos(glm::radians(yaw)) * 3;
//	pos.z = targ.z - sin(glm::radians(yaw)) * 3;
//	direction = normalize(pos - targ);
//	vec3 temp_up = vec3(0.0f, 1.0f, 0.0f);
//	right = normalize((temp_up, direction));
//	up = cross(direction, right);
//	view = look_at(pos, targ, up);
//}