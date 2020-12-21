//
// Created by Jeromy Black on 12/19/20.
//

#include "Animator.h"

Animator::Animator()
{
	animations["run"].emplace_back();
//	animations[0].AddAnimationKey(new AnimationKey(20.0f, vec3(0,0,0) , vec3(0,0,0),vec3(0,0,0)));
//	animations[0].AddAnimationKey(new AnimationKey(20.0f,vec3(0,0,0), vec3(90,0,0), vec3(0,0,0)));
//	animations[0].AddAnimationKey(new AnimationKey(20.0f, vec3(0,0,0) , vec3(180,0,0),vec3(0,0,0)));
//	animations[0].AddAnimationKey(new AnimationKey(20.0f, vec3(0,0,0) , vec3(90,0,0),vec3(0,0,0)));

	animations["run"][0].AddAnimationKey(new AnimationKey(20.0f, vec3(0,0,0) , vec3(0,0,0),vec3(1,1,1)));
	animations["run"][0].AddAnimationKey(new AnimationKey(20.0f, vec3(0,0,0) , vec3(0,90,0),vec3(1,1,1)));
	animations["run"][0].AddAnimationKey(new AnimationKey(20.0f, vec3(0,0,0) , vec3(0,90,0), vec3(1,1,1)));
	animations["run"][0].AddAnimationKey(new AnimationKey(20.0f, vec3(0,0,0) , vec3(0,0,0), vec3(1,1,1)));





//	animations[0].AddAnimationKey(new AnimationKey(5.0f, vec3(0,0,0) , vec3(180,0,0),vec3(0,0,0)));
//	animations[0].AddAnimationKey(new AnimationKey(5.0f, vec3(0,0,0) , vec3(180,0,0),vec3(0,0,0)));




//	animations[0].keys.emplace_back(new AnimationKey(6.0f, vec3(0,0,0) , vec3(0,0,0),vec3(0,0,0)));
//	animations[0].keys.emplace_back(new AnimationKey(9.0f, vec3(0,0,0) , vec3(-180,0,0),vec3(0,0,0)));





//	AnimationKey l1(3.0f,mat4(1), rotation, mat4(1));
//	animations.at(0).keys.push_back(l1);
}