#ifndef DISPLAY_H
#define DISPLAY_H
#pragma once
#include "vox.hpp"
#include "shader.h"
#include <memory>
    // settings
	struct DestroyglfwWin{

    void operator()(GLFWwindow* ptr){
         glfwDestroyWindow(ptr);
    }

	};
namespace Display
{
    // std::unique_ptr<GLFWwindow, DestroyglfwWin> window;
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    void init();
    void close();
    void clear();
    void update();
    GLFWwindow * getWindow();
};


#endif