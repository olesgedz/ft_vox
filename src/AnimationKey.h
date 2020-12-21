//
// Created by Jeromy Black on 12/19/20.
//

#ifndef HUMAGL_ANIMATIONKEY_H
#define HUMAGL_ANIMATIONKEY_H

#include "Maths.h"
class AnimationKey
{
	public:
	vec3 position;
	vec3 rotation;
	vec3 scale;
	vec3 rotationPoint;

	float frameTime;
	float startTime;
//	float finishTime;
	AnimationKey(float time, vec3 p, vec3 r , vec3 s) : position(p), rotation(r), scale(s), frameTime(time)
	{

	}
	private:
};


#endif //HUMAGL_ANIMATIONKEY_H
