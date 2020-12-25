//
// Created by kaygalle on 19.05.2020.
//

#ifndef MINECRAFT_BLOCK_HPP
#define MINECRAFT_BLOCK_HPP

#include <glm/glm.hpp>
#include <vector>
#include <array>

#include "Quad.hpp"

class Chunk;
class Block
{
    public:
    enum BlockType
        {
            GROUND,
            DIRT,
            SAND,
            STONE,
            AIR
        };
        Block(BlockType b_type, int * pos, bool * neighbors, Chunk * chunk);
        std::vector <float> m_vertices;
        std::vector <int> m_indices;
    private:
        Chunk * parent;
        BlockType m_type;
        int * m_pos;
        int indices_multiplier = 0;
        void setTex(BlockType b_type, Quad::QuadType q_type, float * texCoords);
        void pushFace(Quad::QuadType type, float * texCoords);
        void createMesh(bool * neighbors);
};

#endif