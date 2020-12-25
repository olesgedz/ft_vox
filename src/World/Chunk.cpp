//
// Created by Jeromy Black on 12/25/20.
//

#include "Chunk.h"
#include "Quad.h"

void Chunk::generate()
{
	model.meshes.emplace_back();
	Quad(Quad::QuadType::FRONT, &model.meshes[0]);
	for (auto index : Quad::m_indices)
		model.meshes[0].vertexIndices.push_back(index);
}