//
// Created by Jeromy Black on 12/25/20.
//

#include "Chunk.h"
#include "Quad.h"
#include <cmath>
FastNoiseLite Chunk::noise = FastNoiseLite();

void Chunk::generate()
{
	//model.meshes[0].vertices.push_back(vec3(0,0,0));
//	vec3 a =  vec3(0,0,0);
//	Quad(Quad::QuadType::FRONT, this,a);
}

Chunk::~Chunk()
{
}
Chunk::Chunk(vec3 p)
{
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	model.meshes.emplace_back();
//	Shader * shader = new Shader("shaders/SimpleVertex.glsl", "shaders/SimpleFragment.glsl");


	pos = p;
	c = this;
	matrix = allocateChunk();
	generateTerrain();
	for(int x = 0; x < horizontal; x++)
	{
		for(int y = 0; y < vertical; y++)
		{
			for(int z = 0; z < depth; z++)
			{
				matrix [x][y][z] = BlockType::AIR;
				if (y == heightMap [x] [z])
				{
					matrix[x][y][z] = BlockType::GROUND;
				}
				if (y < heightMap [x] [z] && y > heightMap [x] [z] / 2)
					matrix[x][y][z] = BlockType::DIRT;
				if (y < heightMap [x] [z] / 2 + 1)
				{
					matrix[x][y][z] = BlockType::STONE;
				}
				if ((y >= heightMap [x] [z] + 1) && matrix[x][y - 1][z] == BlockType::STONE)
				{
					matrix[x][y][z] = BlockType::WATER;
				}
				if (y > 10 && matrix[x][y - 1][z] == BlockType::GROUND)
				{
					if ( 0.9f < noise.GetNoise(5.3f * ((float) (pos.x + x)) + 30310,5.3f * ((float) (pos.y + y) + 3130)))
						matrix[x][y][z] = BlockType::FLOWER;
				}

				//cout << (int)heightMap [x][z] << " ";
			}
			//cout << endl;
		}
	}
	setNeighbors();
	//glInitialize();
//	bool neighbors[6] = {false};
//	vec3 a = vec3(0,0,0);
//	setBlock(BlockType::GROUND, a, neighbors);
	for (int x = 0; x < Chunk::horizontal; x++)
	{
		for (int y = 0; y < Chunk::vertical; y++)
			delete matrix[x][y];
		delete matrix[x];
	}
	delete [] matrix;


	for (int x = 0; x < Chunk::horizontal; x++)
	{
		delete heightMap[x];//= new int[Chunk::depth];
	}

	delete [] heightMap;
}


BlockType *** Chunk::allocateChunk()
{
	BlockType *** newMatrix;

	newMatrix = new BlockType**[Chunk::horizontal];
	for (int x = 0; x < Chunk::horizontal; x++)
	{
		newMatrix[x] = new BlockType*[Chunk::vertical];
		for (int y = 0; y < Chunk::vertical; y++)
		{

			newMatrix[x][y] = new BlockType[Chunk::depth];
////			for (int z = 0; z < Chunk::depth; z++)
////				cout << (int)newMatrix[x][y][z] << " " << x << endl;
//
		}
	}

//	for (int x = 0; x < Chunk::horizontal; x++)
//	{
//		for (int y = 0; y < Chunk::vertical; y++)
//		{
//			for (int z = 0; z < Chunk::depth; z++)
//			{
//				cout << (int)newMatrix[x][y][z] << endl;
//			}
//		}
//	}
	return newMatrix;
}


void Chunk::setBlock(BlockType b_type, vec3 &pos, bool *neighbors)
{
	Block(b_type, pos, neighbors, this);

//	for (float &m_vertice : temp.m_vertices)
//		m_vertices.push_back(m_vertice);
//	for (int &m_indice : temp.m_indices)
//		m_indices.push_back(m_indice + indices_multiplier);
//	indices_multiplier += temp.m_indices.size() / 6 * 4;
}

void Chunk::setNeighbors()
{
	//pos - x y z
	//neighbors - L R D U B F
	for(int x = 0; x < horizontal; x++)
	{
		for(int y = 0; y < vertical; y++)
		{
			for(int z = 0; z < depth; z++)
			{
				bool neighbors[6] = {false}; // why do you have
				vec3 posl = {x + pos.x, y + pos.y, z + pos.z};
				if(x > 0 && matrix[x - 1] [y][z] != BlockType::AIR &&  matrix[x - 1] [y][z] != BlockType::WATER &&matrix[x - 1] [y][z] != BlockType::FLOWER)
					neighbors [0] = true;
				if(x < horizontal - 1 && matrix[x + 1] [y][z] != BlockType::AIR && matrix[x + 1] [y][z] != BlockType::WATER && matrix[x + 1] [y][z] != BlockType::FLOWER)
					neighbors [1] = true;
				if(y < vertical - 1 && matrix[x] [y + 1][z] != BlockType::AIR && matrix[x] [y + 1][z] != BlockType::WATER && matrix[x] [y + 1][z] != BlockType::FLOWER)
					neighbors [3] = true;
				if(y > 0 && matrix[x] [y - 1][z] != BlockType::AIR && matrix[x] [y - 1][z] != BlockType::WATER && matrix[x] [y - 1][z] != BlockType::FLOWER )
					neighbors [2] = true;
				if(z < depth - 1 && matrix[x] [y] [z + 1] != BlockType::AIR && matrix[x] [y] [z + 1] != BlockType::WATER && matrix[x] [y] [z + 1] != BlockType::FLOWER)
					neighbors [5] = true;
				if(z > 0 && matrix[x] [y][z - 1] != BlockType::AIR &&  matrix[x] [y][z - 1] != BlockType::WATER &&  matrix[x] [y][z - 1] != BlockType::FLOWER )
					neighbors [4] = true;
				if(matrix[x][y][z] != BlockType::AIR)
					setBlock(BlockType(matrix[x][y][z]), posl, neighbors);
			}
		}
	}
}

void Chunk::generateTerrain()
{

	heightMap = new int *[Chunk::horizontal];
	for (int x = 0; x < Chunk::horizontal; x++)
	{
		heightMap[x] = new int[Chunk::depth];
	}
	for (int x = 0; x < Chunk::horizontal; x++)
	{
		for (int z = 0; z < Chunk::depth; z++)
		{
			//float n = m_noise.fracNoise3D(20.03 * (pos.x + x), 0 ,  20.007 * (pos.z + z));
//			if (n > 1)
//				n = 1;
			//heightMap [x][z] = int((n + 1) * Chunk::vertical) / 2;
			float n1 = 1 * noise.GetNoise(0.3f * ((float) (pos.x + x)) + 30310, 0.3f * ((float) (pos.z + z) + 3130));
			float n2 = 0.2 * noise.GetNoise(2.3f * ((float) (pos.x + x)) + 30310, 2.3f * ((float) (pos.z + z) + 3130));
			float n3 = 0.45 * noise.GetNoise(5.3f * ((float) (pos.x + x)) + 30310, 5.3f * ((float) (pos.z + z) + 3130));


			heightMap[x][z] = abs(  (n1 + n2 + n3 / 3.0f)) * vertical * 1.5 ;
//			heightMap [x][z] = int(heightMap [x] [z]) - 1;
//		}
		}
	}
}
