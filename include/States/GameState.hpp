#ifndef GAMESTATE_HPP
# define GAMESTATE_HPP
#include "Renderer/Entity.hpp"
#include "Renderer/Master.hpp"
class Application;
class Camera;
namespace State
{
    class GameState
    {
        public:
		  GameState (Application &application);
		  virtual ~GameState(){};
		  virtual void input(Camera& camera) = 0;
		  virtual void update(Camera& camera, float delta) = 0;
		  virtual void draw(Renderer::Master &renderer) = 0;
        
        protected:
            Application * m_application;
    };
}

#endif