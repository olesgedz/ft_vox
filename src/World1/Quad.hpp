#ifndef MINECRAFT_QUAD_HPP
#define MINECRAFT_QUAD_HPP

#include <glm/glm.hpp>
#include <vector>
#include <array>

class Quad
{
    public:
        enum QuadType
        {
            LEFT,
            RIGHT,
            BOTTOM,
            TOP,
            BACK,
            FRONT,
            LAST
        };
    Quad (QuadType type);
    static unsigned int m_indices[6];
    std::vector<float> m_vertices;
    private:


};

#endif