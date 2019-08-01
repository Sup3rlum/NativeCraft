#pragma once

#include "nchfx.h"

using namespace glm;

typedef struct Vertex
{
	vec3 _position;
	vec3 _normal;
	vec2 _texCoord;

	Vertex(vec3 pos, vec3 norm, vec2 tex)
	{
		_position = pos;
		_normal = norm;
		_texCoord = tex;
	}

};