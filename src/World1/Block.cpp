//
// Created by kaygalle on 19.05.2020.
//

#include <iostream>
#include "Block.hpp"
#include "AtlasSlicer.hpp"
#include "Chunk.hpp"
#include "glm/glm.hpp"

Block::Block(BlockType b_type, int * pos, bool * neighbors, Chunk * chunk) : parent(chunk)
{
    m_type = b_type;
    m_pos = pos;
    createMesh(neighbors);
}

void Block::createMesh(bool * neighbors)
{
    float temp[8];
    for(int i = 0; i < Quad::LAST; i++)
    {
        if(!neighbors[i])
        {
            setTex(m_type, Quad::QuadType(i), temp);
            pushFace(Quad::QuadType(i), temp);
        }
    }
}

void Block::setTex(BlockType b_type, Quad::QuadType q_type, float * texCoords)
{
    int tab = int(AtlasSlicer::uv[b_type * 6 + q_type].x);
    int row = int(AtlasSlicer::uv[b_type * 6 + q_type].y);

    float uv00x = float(tab - 1) / float(SIDE);
    float uv00y = float(row - 1) / float(SIDE);
    float uv01x = float(tab - 1) / float(SIDE);
    float uv01y = float(row) / float(SIDE);
    float uv10x = float(tab) / float(SIDE);
    float uv10y = float(row - 1) / float(SIDE);
    float uv11x = float(tab) / float(SIDE);
    float uv11y = float(row) / float(SIDE);
    switch(q_type) {
        case Quad::LEFT:
            texCoords[0] = uv00x;
            texCoords[1] = uv00y;
            texCoords[2] = uv01x;
            texCoords[3] = uv01y;
            texCoords[4] = uv11x;
            texCoords[5] = uv11y;
            texCoords[6] = uv10x;
            texCoords[7] = uv10y;
            break;
        case Quad::RIGHT:
            texCoords[0] = uv01x;
            texCoords[1] = uv01y;
            texCoords[2] = uv00x;
            texCoords[3] = uv00y;
            texCoords[4] = uv10x;
            texCoords[5] = uv10y;
            texCoords[6] = uv11x;
            texCoords[7] = uv11y;
            break;
        case Quad::BOTTOM:
            texCoords[0] = uv00x;
            texCoords[1] = uv00y;
            texCoords[2] = uv01x;
            texCoords[3] = uv01y;
            texCoords[4] = uv11x;
            texCoords[5] = uv11y;
            texCoords[6] = uv10x;
            texCoords[7] = uv10y;
            break;
        case Quad::TOP:
            texCoords[0] = uv00x;
            texCoords[1] = uv00y;
            texCoords[2] = uv01x;
            texCoords[3] = uv01y;
            texCoords[4] = uv11x;
            texCoords[5] = uv11y;
            texCoords[6] = uv10x;
            texCoords[7] = uv10y;
            break;
        case Quad::FRONT:
            texCoords[0] = uv11x;
            texCoords[1] = uv11y;
            texCoords[2] = uv10x;
            texCoords[3] = uv10y;
            texCoords[4] = uv00x;
            texCoords[5] = uv00y;
            texCoords[6] = uv01x;
            texCoords[7] = uv01y;
            break;
        case Quad::BACK:
            texCoords[0] = uv11x;
            texCoords[1] = uv11y;
            texCoords[2] = uv10x;
            texCoords[3] = uv10y;
            texCoords[4] = uv00x;
            texCoords[5] = uv00y;
            texCoords[6] = uv01x;
            texCoords[7] = uv01y;
            break;
        case Quad::LAST:
            break;
        default:
            break;
    }
}
void Block::pushFace(Quad::QuadType type, float * texCoords)
{
    Quad temp = Quad(type);
    int tex_index = 0;
    for(int i = 0; i < 12; i++)
    {
        if(i % 3 == 0)
            m_vertices.push_back(temp.m_vertices[i] + m_pos[0]);
        else
        if((i + 1) % 3 == 0)
            m_vertices.push_back(temp.m_vertices[i] + m_pos[2]);
        else
            m_vertices.push_back(temp.m_vertices[i] + m_pos[1]);

        if((i + 1) % 3 == 0 && tex_index < 8) {
            m_vertices.push_back(texCoords[tex_index]);
            m_vertices.push_back(texCoords[tex_index + 1]);
            tex_index += 2;
        }
    }
    parent->rigidbody.push_back(glm::vec3 (m_pos[0] - 0.5f, m_pos[1] - 0.5f, m_pos[2] - 1));
    parent->rigidbody.push_back(glm::vec3 (m_pos[0] + 0.5f, m_pos[1] + 0.5f, m_pos[2]));
    for(unsigned int m_indice : Quad::m_indices)
    {
        m_indices.push_back(m_indice + indices_multiplier);
    }
    indices_multiplier+=4;
}

