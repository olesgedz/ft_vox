//
// Created by kaygalle on 22.05.2020.
//

#ifndef MINECRAFT_CHUNK_HPP
#define MINECRAFT_CHUNK_HPP


#include <vector>
#include <array>
#include "Block.hpp"
#include "PerlinNoise/PerlinNoise.h"
#include "glm/glm.hpp"
#include "Camera.hpp"
class Chunk
{
    private:
        Chunk * c;
        static PerlinNoise m_noise;
        int m_pos [3];
        unsigned int VBO{}, VAO{}, EBO{};
        static constexpr int horizontal = 16;
        static constexpr int vertical = 25;
        const int depth = 2;
        char ***matrix;
        int **heightMap;
        void setBlock(Block::BlockType b_type, int * pos, bool * neighbors);
        char *** allocateChunk();
        void generateTerrain();
        void setNeighbors();
        void glInitialize();
    public:
        Chunk(int * pos);
        std::vector<float> m_vertices;
        std::vector<int> m_indices;

        //
        std::vector<glm::vec3> rigidbody;
        //
        int indices_multiplier = 0;

        void render();
        float cast(Camera &camera);
        float boxCast(Camera &camera, glm::vec3 min, glm::vec3 max, glm::mat4 ModelMatrix);
};


#endif //MINECRAFT_CHUNK_HPP
