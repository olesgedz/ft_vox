//
// Created by Jeromy Black on 12/19/20.
//

#include "Animation.h"
#include "glad.h"
#include "GLFW/glfw3.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Maths.h"
#include <iostream>



int Animation::FindKey()
{
	int i = 0;
	for (; i < keys.size() - 1; i++)
	{
		if (timeFromStart < (float) keys[i + 1]->startTime)
			return i;
	}
	if (i == keys.size() - 1)
		return i;

	return 0 ;
}
vec3 Animation::GetPosition(const Entity& entity, float time)
{
	if (keys.size() == 1)
		return keys[0]->position;
	int startFrame = FindKey();
	int endFrame =  startFrame >= (keys.size() - 1) ? 0 : startFrame + 1;
	float DeltaTime = 0;
	float Factor = 0;
	if (endFrame == 0)
	{
		DeltaTime = keys[0]->frameTime ;
		Factor = (timeFromStart - keys[startFrame]->startTime) / DeltaTime;
	}
	else
	{
		DeltaTime = keys[endFrame]->startTime - keys[startFrame]->startTime;
		Factor = (timeFromStart - keys[startFrame]->startTime) / DeltaTime;
	}
	vec3 r = lerp(keys[startFrame]->position, keys[endFrame]->position, Factor);

	return r;
}
vec3 Animation::GetRotationMatrix(const Entity& entity, float time)
{
	if (keys.size() == 1)
		return keys[0]->rotation;
	int startFrame = FindKey();
	int endFrame =  startFrame >= (keys.size() - 1) ? 0 : startFrame + 1;
	float DeltaTime = 0;
	float Factor = 0;
	if (endFrame == 0)
	{
		 DeltaTime = keys[0]->frameTime ;
		 Factor = (timeFromStart - keys[startFrame]->startTime) / DeltaTime;
	}
	else
	{
		 DeltaTime = keys[endFrame]->startTime - keys[startFrame]->startTime;
		 Factor = (timeFromStart - keys[startFrame]->startTime) / DeltaTime;
	}
 	vec3 r = lerp(keys[startFrame]->rotation, keys[endFrame]->rotation, Factor);
	return r;
}
vec3 Animation::GetScale(const Entity& entity, float time)
{
	if (keys.size() == 1)
		return keys[0]->rotation;
	int startFrame = FindKey();
	int endFrame =  startFrame >= (keys.size() - 1) ? 0 : startFrame + 1;
	float DeltaTime = 0;
	float Factor = 0;
	if (endFrame == 0)
	{
		DeltaTime = keys[0]->frameTime ;
		Factor = (timeFromStart - keys[startFrame]->startTime) / DeltaTime;
	}
	else
	{
		DeltaTime = keys[endFrame]->startTime - keys[startFrame]->startTime;
		Factor = (timeFromStart - keys[startFrame]->startTime) / DeltaTime;
	}
	vec3 r = lerp(keys[startFrame]->scale, keys[endFrame]->scale, Factor);
	return r;
}

mat4 Animation::GetAnimationMatrix(const Entity& entity, float time)
{
	timeFromStart += time;

	if (timeFromStart >= duration)
		timeFromStart = 0;
	std::cout << timeFromStart << std::endl;
	std::cout << "Duration" << duration << std::endl;
	int key = FindKey();

	mat4 result = mat4(1.0f);
	result = translate(result, GetPosition(entity, time));
	result = translate(result,   entity.positionOffset);
	result = rotate(result, GetRotationMatrix(entity, time));
	result = translate(result, -1 * entity.positionOffset);
	result = scale(result, GetScale(entity, time));

	return result;
}

void Animation::AddAnimationKey(AnimationKey *key)
{
		key->startTime = duration;
		keys.emplace_back(key);
		duration += key->frameTime;

}

Animation::Animation()
{

}

//Animation::Animation(const std::vector<AnimationKey> &keys) : keys(keys)
//{
//
//}
