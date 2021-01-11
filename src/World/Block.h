//
// Created by Jeromy Black on 12/25/20.
//

#ifndef FT_VOX_BLOCK_H
#define FT_VOX_BLOCK_H


#include <glm/glm.hpp>
#include <vector>
#include <array>

#include "Quad.h"

class Chunk;
enum class BlockType
{
	GROUND,
	DIRT,
	SAND,
	STONE,
	WATER,
	FLOWER,
	AIR
};
class Block
{
public:

	Block(BlockType b_type, vec3& pos, bool * neighbors, Chunk * chunk);
private:
	Chunk * parent;
	BlockType m_type;
	vec3 m_pos;
	int indices_multiplier = 0;
	void setTex(BlockType b_type, Quad::QuadType q_type, float * texCoords);
	void pushFace(Quad::QuadType type, float * texCoords);
	void createMesh(bool * neighbors);
};

#endif //FT_VOX_BLOCK_H
