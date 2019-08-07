#include "BoundingBox.h"

BoundingBox::BoundingBox(vec3 min, vec3 max)
{
	Min = min;
	Max = max;
	Rotation = identity<mat4>();
}

BoundingBox::BoundingBox(vec3 min, vec3 max, mat4 rot)
{
	Min = min;
	Max = max;
	Rotation = rot;
}


bool BoundingBox::Contains(vec3 p)
{
	return	(p.x > Min.x) &&
		(p.y > Min.y) &&
		(p.z > Min.z) &&

		(p.x < Max.x) &&
		(p.y < Max.y) &&
		(p.z < Max.z);
}