#include "Camera.h"


Camera::Camera()
{
	horizontalAngle = -3.14159265f / 2.0f;
	verticalAngle = -3.14159265f / 4.0f;

	Projection = perspective(radians(Fov), 16.0f / 9.0f, 0.1f, 100.0f);

	Position = vec3(4.0f, 4.0f, 4.0f);
}
Camera::~Camera()
{

}

void Camera::Update(GLFWwindow* _window, ContextParameters* _params, FrameTime* _frTime)
{
	double xpos, ypos;

	glfwGetCursorPos(_window, &xpos, &ypos);

	glfwSetCursorPos(
		_window, 
		_params->width / 2.0, 
		_params->height / 2.0);

	horizontalAngle += mouseSpeed * _frTime->DeltaTime * (_params->width / 2.0 - xpos);
	verticalAngle	+= mouseSpeed * _frTime->DeltaTime * (_params->height / 2.0 - ypos);

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

	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) 
	{
		Position += Target * (float)_frTime->DeltaTime * flySpeed;
	}
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) 
	{
		Position -= Target * (float)_frTime->DeltaTime * flySpeed;
	}
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) 
	{
		Position += Right * (float)_frTime->DeltaTime * flySpeed;
	}
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) 
	{
		Position -= Right * (float)_frTime->DeltaTime * flySpeed;
	}

	View = lookAt(Position, Position + Target, Up);
}