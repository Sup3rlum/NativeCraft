#pragma once



#include "nchfx.h"

#include "FrameTime.h"
#include "Camera.h"
#include "Scene.h"

using namespace glm;



class Context
{
public:
	static GLFWwindow* _window;
	static ContextParameters* _contextParameters;
	static FrameTime* _frameTime;
	static Camera* _camera;

	static int Initialize(ContextParameters* _params);
	static void Frame(FrameTime* _frTime);
	static void Update(FrameTime* _frTime);

	static int InitGLEW();
	static int InitGLFW();

};

