//
// Created by Jeromy Black on 12/19/20.
//

#ifndef HUMAGL_ANIMATOR_H
#define HUMAGL_ANIMATOR_H

#include <vector>
#include "Animation.h"
#include <map>
#include <string>

class Animator
{
	public:
		std::map<std::string, std::vector<Animation>> animations;
		Animator();
		~Animator() = default;
	private:
};


#endif //HUMAGL_ANIMATOR_H
