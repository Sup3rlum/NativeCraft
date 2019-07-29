#include "Context.h"



GLFWwindow*			Context::_window			= NULL;
ContextParameters*	Context::_contextParameters	= NULL;
FrameTime*			Context::_frameTime			= NULL;
Scene*				Context::_scene				= NULL;


int Context::Initialize(ContextParameters* _params)
{

	_contextParameters = _params;

	InitGLFW();
	InitGLEW();

	_frameTime = new FrameTime();
	_scene = new Scene();

	// Main Loop
	do
	{
		_frameTime->DeltaTime = glfwGetTime() - _frameTime->TotalTime;
		_frameTime->TotalTime = glfwGetTime();

		glCullFace(GL_FRONT_AND_BACK);
		glEnable(GL_DEPTH_TEST);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.5f, 1.0f, 1.0f);


		Update(_frameTime);
		Frame(_frameTime);

		glfwSwapBuffers(_window);
		glfwPollEvents();

	} 
	while (glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(_window) == 0);

	return 0;
}
void Context::Frame(FrameTime* _frTime)
{
	_scene->Render(_frameTime);
}
void Context::Update(FrameTime* _frTime)
{
	_scene->Update(_window, _contextParameters, _frameTime);
}

int Context::InitGLEW()
{
	glewExperimental = true;

	GLuint _initResult = glewInit();

	if (_initResult != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	else
	{
		return 0;
	}
}
int Context::InitGLFW()
{

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	// GLFW Context

	glfwWindowHint(GLFW_SAMPLES,					_contextParameters->contextSampleCount);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,		_contextParameters->contextMajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,		_contextParameters->contextMinorVersion);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,		_contextParameters->contextCompatibility);
	glfwWindowHint(GLFW_OPENGL_PROFILE,				_contextParameters->contextProfile);

	_window = glfwCreateWindow(_contextParameters->width, _contextParameters->height, "NativeCraft", NULL, NULL);

	if (_window == NULL)
	{
		fprintf(stderr, "OpenGL 3.3 is not supported by this PC");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(_window);

	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}