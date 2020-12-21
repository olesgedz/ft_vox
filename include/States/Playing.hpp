#ifndef PLAYING_HPP
#define PLAYING_HPP
#include "States/GameState.hpp"
#include "Model.hpp"
#include "Shader/SimpleShader.hpp"
#include "Texture.hpp"
#include "Renderer/Master.hpp"
#include "Renderer/Quad.hpp"

class Camera;
class Application;
namespace State {
class Playing : public GameState {
 public:
  Playing(Application &application);
  void input(Camera& camera) override;
  void update(Camera& camera, float delta) override;
  void draw(Renderer::Master &renderer) override;
 private:
  Shader::SimpleShader m_shader;
  BasicTexture m_texture;

  Quad m_quad;
};
}
#endif