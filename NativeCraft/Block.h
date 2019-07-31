#pragma once

#include "nchfx.h"

using namespace glm;

typedef struct Block
{
	vec3 _position;
	float _id;

	Block(vec3 pos, float id)
	{
		_position = pos;
		_id = id;
	}

};