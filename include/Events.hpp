//
// Created by Oles Gedz on 23/06/2020.
//

#ifndef FT_VOX_INCLUDE_EVENTS_HPP_
#define FT_VOX_INCLUDE_EVENTS_HPP_
#include "vox.hpp"
class Events {

 public:
  static float xoffset;
  static float yoffset;

  static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
  static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
  static void processInput(GLFWwindow *window);
  static float getOffsetX(){ return xoffset;};
  static float getOffsetY(){ return yoffset;};


};

#endif //FT_VOX_INCLUDE_EVENTS_HPP_
