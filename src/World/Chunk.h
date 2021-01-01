//
// Created by Jeromy Black on 12/25/20.
//

#ifndef FT_VOX_CHUNK_H
#define FT_VOX_CHUNK_H
#include "Model.h"
#include "Block.h"
#include "PerlinNoise.h"
#include "FastNoiseLite.h"

class Chunk
{
	public:
		Model model;
		void generate();
	static constexpr int horizontal = 10;
	static constexpr int vertical = 10;
	const int depth = 10;
	static PerlinNoise m_noise;
	static FastNoiseLite noise;
	vec3 pos;
	Chunk * c;
	BlockType ***matrix;
	int **heightMap;
	void setBlock(BlockType b_type,  vec3 &pos, bool * neighbors);
	BlockType *** allocateChunk();
	void generateTerrain();
	void setNeighbors();
	int n_vertices = 0;
	//void glInitialize();
	Chunk(vec3 pos);
//	private:


};


#endif //FT_VOX_CHUNK_H
