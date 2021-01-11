//
// Created by Jeromy Black on 12/25/20.
//

#include "AtlasSlicer.h"
#include <glm/glm.hpp>

#include "AtlasSlicer.h"

/*
   0         1         2        3      4       5
   L_side   R_side  D_side  U_side  B_side  F_side
                    x - tab y - row
             SAME WITH BLOCKTYPE ENUM
*/

/* [0 : 5] - GROUND */
const glm::vec2 AtlasSlicer::uv [] =
		{
				glm::vec2 (12, 15), glm::vec2 (12, 15),  // L, R
				glm::vec2 (15, 17), glm::vec2 (3, 14),   // Bottom, Top    //GROUND
				glm::vec2 (12, 15), glm::vec2 (12, 15),  // B, F

				glm::vec2 (15, 17), glm::vec2 (15, 17),  // L, R
				glm::vec2 (15, 17), glm::vec2 (15, 17),   // Bottom, Top   //DIRT
				glm::vec2 (15, 17), glm::vec2 (15, 17),  // B, F

				glm::vec2 (3, 2), glm::vec2 (3, 2),  // L, R
				glm::vec2 (3, 2), glm::vec2 (3, 2),   // Bottom, Top       //SAND
				glm::vec2 (3, 2), glm::vec2 (3, 2),  // B, F

				glm::vec2 (13, 5), glm::vec2 (13, 5),  // L, R
				glm::vec2 (13, 5), glm::vec2 (13, 5),   // Bottom, T       //STONE
				glm::vec2 (13, 5), glm::vec2 (13, 5),   // B, F

				glm::vec2 (11, 12), glm::vec2 (11, 12), // L, R
				glm::vec2 (11, 12), glm::vec2 (11, 12),   // Bottom, T       //WATER
				glm::vec2 (11, 12), glm::vec2 (11, 12),   // B, F

				glm::vec2 (7, 22), glm::vec2 (7, 22),  // L, R
				glm::vec2 (7, 22), glm::vec2 (7, 22),   // Bottom, Top       //Flowe
				glm::vec2 (7, 22), glm::vec2 (7, 22)  // B, F
		};