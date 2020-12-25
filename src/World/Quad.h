//
// Created by Jeromy Black on 12/25/20.
//

#ifndef FT_VOX_QUAD_H
#define FT_VOX_QUAD_H

#include "Mesh.h"
#include <glm/glm.hpp>
#include <vector>
#include <array>

class Quad
{
public:
	enum QuadType
	{
		LEFT,
		RIGHT,
		BOTTOM,
		TOP,
		BACK,
		FRONT,
		LAST
	};
	Quad (QuadType type, Mesh * mesh);
	Quad (QuadType type);

	static unsigned int m_indices[6];
	std::vector<float> m_vertices;
private:


};

#endif //FT_VOX_QUAD_H
