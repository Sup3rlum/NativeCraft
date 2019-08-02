#pragma once

#include "nchfx.h"
#include "VertexElements.h"

using namespace glm;
using namespace std;

typedef struct VertexNormalTexture
{
	vec3 _position;
	vec3 _normal;
	vec2 _texCoord;

	VertexNormalTexture(vec3 pos, vec3 norm, vec2 tex)
	{
		_position = pos;
		_normal = norm;
		_texCoord = tex;
	}

	static vector<VertexElements> Elements;
};

typedef struct VertexTexture
{
	vec3 _position;
	vec2 _texCoord;

	VertexTexture(vec3 pos, vec2 tex)
	{
		_position = pos;
		_texCoord = tex;
	}

	static vector<VertexElements> Elements;
};