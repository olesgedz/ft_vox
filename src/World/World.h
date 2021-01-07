//
// Created by Jeromy Black on 1/7/21.
//

#ifndef FT_VOX_WORLD_H
#define FT_VOX_WORLD_H
#include <map>
#include "glm/glm.hpp"
#include "Chunk.h"

class World
{
	std::map<glm::vec2, Chunk *> world;
};


#endif //FT_VOX_WORLD_H
