//
// Created by Jeromy Black on 12/19/20.
//

#ifndef HUMAGL_ANIMATION_H
#define HUMAGL_ANIMATION_H
#include "glm/glm.hpp"
#include <vector>
#include "AnimationKey.h"
#include "Entity.h"
#include "glm/glm.hpp"
using  namespace  glm;
class Animation
{
	public:
		Animation();
	//	Animation(const std::vector<AnimationKey> &keys);



	Animation(const std::vector<AnimationKey *> &keys);

private:
	float duration = 0;
	float timeFromStart = 0;


};


#endif //HUMAGL_ANIMATION_H
