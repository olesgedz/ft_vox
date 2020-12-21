//
// Created by Oles Gedz on 23/06/2020.
//

#ifndef FT_VOX_INCLUDE_MATRIX_HPP_
#define FT_VOX_INCLUDE_MATRIX_HPP_
#include <glm/gtx/string_cast.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer/Entity.hpp"

#include "Camera.hpp"

namespace Matrix
{
	glm::mat4 createViewMatrix(const Camera& entity);
	glm::mat4 createModelMatrix(const Entity& entity);
	glm::mat4 createProjMatrix();

}

#endif //FT_VOX_INCLUDE_MATRIX_HPP_
