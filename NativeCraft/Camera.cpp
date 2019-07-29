#include "Camera.h"


Camera::Camera()
{
	horizontalAngle = 0.0f;
	verticalAngle = 3.14159265f;

	Projection == glm::perspective(Fov, 16.0f / 9.0f, 1.0f, 100.0f);
}
Camera::~Camera()
{

}

void Camera::Update(FrameTime* _frTime)
{
	double xpos, ypos;

	glfwGetCursorPos(Context::_window, &xpos, &ypos);

	glfwSetCursorPos(
		Context::_window, 
		Context::_contextParameters->width / 2.0, 
		Context::_contextParameters->height / 2.0);

	horizontalAngle += mouseSpeed * _frTime->DeltaTime * (Context::_contextParameters->width / 2.0 - xpos);
	verticalAngle	+= mouseSpeed * _frTime->DeltaTime * (Context::_contextParameters->height / 2.0 - ypos);

	Target = vec3
	(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	Right = vec3
	(
		sin(horizontalAngle - 1.5708f),
		0,
		cos(horizontalAngle - 1.5708f)
	);

	Up = cross(Right, Target);

	if (glfwGetKey(Context::_window, GLFW_KEY_UP) == GLFW_PRESS) 
	{
		Position += Target * (float)_frTime->DeltaTime * flySpeed;
	}
	if (glfwGetKey(Context::_window, GLFW_KEY_DOWN) == GLFW_PRESS) 
	{
		Position -= Target * (float)_frTime->DeltaTime * flySpeed;
	}
	if (glfwGetKey(Context::_window, GLFW_KEY_RIGHT) == GLFW_PRESS) 
	{
		Position += Right * (float)_frTime->DeltaTime * flySpeed;
	}
	if (glfwGetKey(Context::_window, GLFW_KEY_LEFT) == GLFW_PRESS) 
	{
		Position -= Right * (float)_frTime->DeltaTime * flySpeed;
	}
}