#include "Frustum.h"

Frustum::Frustum(mat4 PV)
{
	vec4 row[4];

	for (int i = 0; i < 4; i++)
	{
		row[i] = transpose(PV)[i];
	}

	zNear =		Plane(row[3] + row[2]);
	zFar =		Plane(row[3] - row[2]);
	Left =		Plane(row[3] + row[0]);
	Right =		Plane(row[3] - row[0]);
	Top =		Plane(row[3] - row[1]);
	Bottom =	Plane(row[3] + row[1]);
}

bool Frustum::Contains(BoundingBox _b)
{
	return Intersects(_b) != IntersectionType::Disjoint;
}
bool Frustum::Contains(vec3 _p)
{
	return Left.DistanceSigned(_p) > 0 && Right.DistanceSigned(_p) > 0 && zNear.DistanceSigned(_p) > 0 && zFar.DistanceSigned(_p) > 0;
}

IntersectionType Frustum::Intersects(BoundingBox _b)
{
	vec3* corns = _b.GetCorners();

	int _t = 0;

	for (int i = 0; i < 8; i++)
	{
		if (Contains(corns[i]))
		{
			_t++;
		}
			
	}

	if (_t == 0)
	{
		return IntersectionType::Disjoint;
	}
	if (_t == 8)
	{
		return IntersectionType::Contains;
	}

	return IntersectionType::Intersects;
}
