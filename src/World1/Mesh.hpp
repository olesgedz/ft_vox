//
// Created by kaygalle on 6/15/20.
//

#ifndef MINECRAFT_MESH_HPP
#define MINECRAFT_MESH_HPP

#include "Camera.hpp"
#include "Chunk.hpp"
#include "ChunkRenderer.hpp"

class Mesh
{
    private:
        std::vector <Chunk> map;
        ChunkRenderer m_chunkRenderer;
        Camera m_camera;
    public:
        void createMap(int chunk_amount);
        void rendererLoop();
};


#endif //MINECRAFT_MESH_HPP
