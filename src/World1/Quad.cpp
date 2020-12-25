#include "Quad.hpp"
static float vFront [] ={
        0.5f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f,   //FRONT
        -0.5f,  0.5f,  0.0f
};
static float vBack [] = {
        0.5f,  0.5f, -1.0f,
        0.5f, -0.5f, -1.0f, //BACK
        -0.5f, -0.5f, -1.0f,
        -0.5f,  0.5f, -1.0f
};
static float vTop [] = {
        -0.5f,  0.5f,  0.0f,
        -0.5f,  0.5f, -1.0f,    //TOP
        0.5f,  0.5f, -1.0f,
        0.5f,  0.5f,  0.0f
};
static float vBottom [] = {
        -0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f, -1.0f,    //DOWN
        0.5f, -0.5f, -1.0f,
        0.5f, -0.5f,  0.0f
};
static float vRight [] = {
        0.5f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,    //RIGHT
        0.5f, -0.5f, -1.0f,
        0.5f,  0.5f, -1.0f
};
static float vLeft [] = {
        -0.5f, -0.5f, -1.0f,
        -0.5f,  0.5f, -1.0f,     //LEFT
        -0.5f,  0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
};
Quad::Quad(QuadType type)
{
    switch (type)
    {
        case FRONT:
            for(float &i : vFront)
                m_vertices.push_back(i);
            break;
        case BACK:
            for(float &i : vBack)
                m_vertices.push_back(i);
            break;
        case LEFT:
            for(float &i : vLeft)
                m_vertices.push_back(i);
            break;
        case RIGHT:
            for(float &i : vRight)
                m_vertices.push_back(i);
            break;
        case TOP:
            for(float &i : vTop)
                m_vertices.push_back(i);
            break;
        case BOTTOM:
            for(float &i : vBottom)
                m_vertices.push_back(i);
            break;
        default:
        break;
    }
}

unsigned int Quad::m_indices[6] = {
    0,  1,  3,
    1,  2,  3
};