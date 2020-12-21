//
// Created by Oles Gedz on 05/06/2020.
//

#ifndef FT_VOX_SIMPLE_HPP
#define FT_VOX_SIMPLE_HPP
#include <vector>
#include "Shader/SimpleShader.hpp"
class Quad;
class Camera;
namespace Renderer {
class Simple {
 public:
  void draw(Quad &quad);
  void update(const Camera& camera);
 private:
  void prepare(Quad &quad);
  std::vector<Quad *> m_quads;
  Shader::SimpleShader m_shader;
};
}

#endif //FT_VOX_SIMPLE_HPP
