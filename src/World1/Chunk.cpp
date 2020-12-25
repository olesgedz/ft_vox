//
// Created by kaygalle on 22.05.2020.
//
#include <glad/glad.h>
#include <iostream>
#include <Camera.hpp>
#include "Chunk.hpp"



//rm
#include <glm/gtx/string_cast.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


PerlinNoise Chunk::m_noise = PerlinNoise();

Chunk::Chunk(int * pos)
{
    m_pos [0] = pos [0];
    m_pos [1] = pos [1];
    m_pos [2] = pos [2];
    c = this;
  	m_noise.setScale(Chunk::horizontal);
  	matrix = allocateChunk();
    generateTerrain();
    for(int x = 0; x < horizontal; x++)
    {
        for(int y = 0; y < vertical; y++)
        {
            for(int z = 0; z < horizontal; z++)
            {
                matrix [x][y][z] = Block::AIR;
                if (y == heightMap [x] [z])
                    matrix[x][y][z] = Block::GROUND;
                if (y < heightMap [x] [z] && y > heightMap [x] [z] / 2)
                    matrix[x][y][z] = Block::DIRT;
                if (y < heightMap [x] [z] / 2 + 1)
                    matrix[x][y][z] = Block::STONE;
            }
        }
    }
    setNeighbors();
    glInitialize();
    delete [] matrix;
    delete [] heightMap;
}


char *** Chunk::allocateChunk()
{
    char *** newMatrix;

    newMatrix = new char**[Chunk::horizontal];
    for (int x = 0; x < Chunk::horizontal; x++)
    {
        newMatrix[x] = new char*[Chunk::vertical];
        for (int y = 0; y < Chunk::vertical; y++)
        {

            newMatrix[x][y] = new char[Chunk::depth];
        }
    }
    return newMatrix;
}


void Chunk::setBlock(Block::BlockType b_type, int * pos, bool *neighbors)
{
    Block temp = Block(b_type, pos, neighbors, this);
    for (float &m_vertice : temp.m_vertices)
        m_vertices.push_back(m_vertice);
    for (int &m_indice : temp.m_indices)
        m_indices.push_back(m_indice + indices_multiplier);
    indices_multiplier += temp.m_indices.size() / 6 * 4;
}

void Chunk::setNeighbors()
{
    //pos - x y z
    //neighbors - L R D U B F
    for(int x = 0; x < horizontal; x++)
    {
        for(int y = 0; y < vertical; y++)
        {
            for(int z = 0; z < horizontal; z++)
            {
                bool neighbors[6] = {false}; // why do you have
                int pos[] = {x + m_pos[0], y + m_pos[1], z + m_pos[2]};
                if(x > 0 && matrix[x - 1] [y][z] != Block::AIR )
                    neighbors [0] = true;
                if(x < horizontal - 1 && matrix[x + 1] [y][z] != Block::AIR )
                    neighbors [1] = true;
                if(y < vertical - 1 && matrix[x] [y + 1][z] != Block::AIR )
                    neighbors [3] = true;
                if(y > 0 && matrix[x] [y - 1][z] != Block::AIR )
                    neighbors [2] = true;
                if(z < horizontal - 1 && matrix[x] [y] [z + 1] != Block::AIR )
                    neighbors [5] = true;
                if(z > 0 && matrix[x] [y][z - 1] != Block::AIR )
                    neighbors [4] = true;
                if(matrix[x][y][z] != Block::AIR)
                    setBlock(Block::BlockType(matrix[x][y][z]), pos, neighbors);
            }
        }
    }
}

void Chunk::generateTerrain()
{
    m_noise.setScale(Chunk::horizontal * 32);
    heightMap = new int*[Chunk::horizontal];
    for (int x = 0; x < Chunk::horizontal; x++)
    {
        heightMap[x] = new int [Chunk::vertical];
    }
    for(int x = 0; x < Chunk::horizontal; x++)
    {
        for(int z = 0; z < Chunk::horizontal; z++)
        {
            float n = m_noise.fracNoise3D(20 * (m_pos[0] + x), 0 ,  20 * (m_pos[2] + z));
            if (n > 1)
                n = 1;
            heightMap [x][z] = int((n + 1) * Chunk::vertical) / 2;
            heightMap [x][z] = int(heightMap [x] [z]) - 1;
        }
    }
}


void Chunk::glInitialize()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Chunk::render()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
}


float Chunk::boxCast(Camera &camera, glm::vec3 min, glm::vec3 max, glm::mat4 ModelMatrix)
{
    // Intersection method from Real-Time Rendering and Essential Mathematics for Games

    float tMin = 0.0f;
    float tMax = 100000.0f;

//    glm::vec3 OBBposition_worldspace(1, 1, 1);
    glm::vec3 OBBposition_worldspace(ModelMatrix[3].x, ModelMatrix[3].y, ModelMatrix[3].z);

    glm::vec3 delta = OBBposition_worldspace - camera.cameraPos;

    // Test intersection with the 2 planes perpendicular to the OBB's X axis
    {
//        glm::vec3 xaxis(camera.view[0].x, camera.view[0].y, camera.view[0].z);
        glm::vec3 xaxis(ModelMatrix[0].x, ModelMatrix[0].y, ModelMatrix[0].z);
        float e = glm::dot(xaxis, delta);
        float f = glm::dot(camera.cameraFront, xaxis);

        if ( fabs(f) > 0.001f ){ // Standard case

            float t1 = (e+min.x)/f; // Intersection with the "left" plane
            float t2 = (e+max.x)/f; // Intersection with the "right" plane
            // t1 and t2 now contain distances betwen ray origin and ray-plane intersections

            // We want t1 to represent the nearest intersection,
            // so if it's not the case, invert t1 and t2
            if (t1>t2){
                float w=t1;t1=t2;t2=w; // swap t1 and t2
            }

            // tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
            if ( t2 < tMax )
                tMax = t2;
            // tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
            if ( t1 > tMin )
                tMin = t1;

            // And here's the trick :
            // If "far" is closer than "near", then there is NO intersection.
            // See the images in the tutorials for the visual explanation.
            if (tMax < tMin )
                return false;

        }else{ // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
            if(-e+min.x > 0.0f || -e+max.x < 0.0f)
                return false;
        }
    }


    // Test intersection with the 2 planes perpendicular to the OBB's Y axis
    // Exactly the same thing than above.
    {
//        glm::vec3 yaxis(camera.view[1].x, camera.view[1].y, camera.view[1].z);
        glm::vec3 yaxis(ModelMatrix[1].x, ModelMatrix[1].y, ModelMatrix[1].z);

        float e = glm::dot(yaxis, delta);
        float f = glm::dot(camera.cameraFront, yaxis);

        if ( fabs(f) > 0.001f ){

            float t1 = (e+min.y)/f;
            float t2 = (e+max.y)/f;

            if (t1>t2){float w=t1;t1=t2;t2=w;}

            if ( t2 < tMax )
                tMax = t2;
            if ( t1 > tMin )
                tMin = t1;
            if (tMin > tMax)
                return false;

        }else{
            if(-e+min.y > 0.0f || -e+max.y < 0.0f)
                return false;
        }
    }


    // Test intersection with the 2 planes perpendicular to the OBB's Z axis
    // Exactly the same thing than above.
    {
//        glm::vec3 zaxis(camera.view[2].x, camera.view[2].y, camera.view[2].z);
        glm::vec3 zaxis(ModelMatrix[2].x, ModelMatrix[2].y, ModelMatrix[2].z);

        float e = glm::dot(zaxis, delta);
        float f = glm::dot(camera.cameraFront, zaxis);

        if ( fabs(f) > 0.001f ){

            float t1 = (e+min.z)/f;
            float t2 = (e+max.z)/f;

            if (t1>t2){float w=t1;t1=t2;t2=w;}

            if ( t2 < tMax )
                tMax = t2;
            if ( t1 > tMin )
                tMin = t1;
            if (tMin > tMax)
                return false;

        }else{
            if(-e+min.z > 0.0f || -e+max.z < 0.0f)
                return false;
        }
    }

    return tMin;

}

float Chunk::cast(Camera &camera)
{
    float res = -1;
    float min = 10000.0f;
    for ( int i = 0; i < rigidbody.size(); i += 2)
    {
        res = boxCast(camera, rigidbody[i], rigidbody[i+1], glm::identity<glm::mat4>());
        if (res > 0 && res < min)
        {
            min = res;
//            return min;
        }
    }
    if (min < 10000.0f)
        return min;
    else
        return -1.0f;
}

