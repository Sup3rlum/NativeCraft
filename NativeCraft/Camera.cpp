#include "Camera.h"


Camera::Camera()
{
	Projection == glm::perspective(Fov, 16.0f / 9.0f, 1.0f, 100.0f);
}