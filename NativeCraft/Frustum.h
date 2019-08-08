#pragma once

#include "nchfx.h"
#include "BoundingBox.h"
#include "Plane.h"

class Frustum
{
public:
	Frustum(mat4 PV);

	bool Contains(BoundingBox _box);
	bool Contains(vec3 _p);

	IntersectionType Intersects(BoundingBox _box);

	Plane zNear, zFar, Left, Right, Top, Bottom;
};

