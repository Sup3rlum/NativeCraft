#pragma once

#include "nchfx.h"

#include "FrameTime.h"
#include "ContextParameters.h"

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

	void Update(GLFWwindow* _window, ContextParameters* _params, FrameTime* _frTime);

	float mouseSpeed = 0.03f;
	float flySpeed = 2.0f;
};

