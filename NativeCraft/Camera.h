#pragma once

#include "nchfx.h"

#include "FrameTime.h"

using namespace glm;

class Camera
{


public:
	Camera();
	~Camera();

	mat4x4 View;
	mat4x4 Projection;
	vec3 Position;
	vec3 Target;
	vec3 Right;
	vec3 Up;

	float Fov = 45.0f;

	float horizontalAngle;
	float verticalAngle;

	void Update(FrameTime* _frTime);

	float mouseSpeed = 0.001f;
	float flySpeed = 0.5f;
};

