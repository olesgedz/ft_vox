//
// Created by kaygalle on 6/15/20.
//

#include "Mesh.hpp"

void Mesh::createMap(int chunk_amount)
{
    //ONLY FOR TEST
    for(int z = 0; z < 80; z+=16)
    {
        for (int x = 0; x < 80; x+=16)
        {
            int chpos[3] = {x, 0, z};
            map.push_back(Chunk (chpos));
        }
    }
    m_chunkRenderer.initialize(map);
    m_camera.initialize(960, 540, &m_chunkRenderer.m_shader);
}

void Mesh::rendererLoop()
{
    m_chunkRenderer.PhysicsLoop(map, m_camera);
    m_chunkRenderer.RendererLoop(map, m_camera);
    m_camera.Process();
    m_camera.cameraInput();
    m_camera.mouseInput();
    m_camera.updateCameraVectors();
}
