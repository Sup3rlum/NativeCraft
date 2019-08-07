#pragma once

#include "nchfx.h"

using namespace glm;

class BoundingBox
{
public:
	vec3 Min;
	vec3 Max;
	mat4 Rotation;

	BoundingBox(vec3 min, vec3 max);
	BoundingBox(vec3 min, vec3 max, mat4 rot);

	bool Contains(vec3 p);

};

