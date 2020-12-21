//
// Created by Oles Gedz on 05/06/2020.
//

#ifndef FT_VOX_MASTER_HPP
#define FT_VOX_MASTER_HPP
#include "Renderer/Simple.hpp"

class Camera;
namespace  Renderer {

    class Master {
    public:
        void update(const Camera& camera);
        void clear();
        void draw(Quad &quad);
     private:
      	Simple m_simpleRenderer;
    };
}

#endif //FT_VOX_MASTER_HPP
