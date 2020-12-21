#pragma once

struct Controls
{
    Controls();
	float	last_x;
	float	last_y;
	float	yaw;
	float	pitch;
	bool	keys[1024];
	bool	first_m = true;
    bool    lock_mouse = true;
};

void	key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void	mouse_callback(GLFWwindow *window, double xpos, double ypos);