#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#pragma once
#include "shader.h"
#include <stack>
#include <memory>
#include "States/GameState.hpp"
#include "Renderer/Master.hpp"
#include "Renderer/Entity.hpp"
#include "Camera.hpp"
class Application
{
    public :
        Application();

        void runMainGameLoop();

        void pushState(std::unique_ptr<State::GameState> m_states);
        void popState();

    private:
        std::stack<std::unique_ptr<State::GameState>> m_states;
        Renderer::Master m_renderer;
  	Camera camera;
};
#endif