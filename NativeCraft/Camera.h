#pragma once

#include "nchfx.h"

using namespace glm;

class Camera
{


public:
	Camera();
	~Camera();

	mat4x4 View;
	mat4x4 Projection;
	vec3 Position;

	float Fov = 45.0f;

	float horizontalAngle;
	float verticalAngle;

	void Update();
};

