#include "Context.h"



GLFWwindow* Context::_window = NULL;
ContextParameters* Context::_contextParameters = NULL;


int Context::Initialize(ContextParameters* _params)
{

	_contextParameters = _params;

	InitGLFW();
	InitGLEW();

	// Main Loop

	do
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.7f, 1.0f, 1.0f);


		Frame();

		glfwSwapBuffers(_window);
		glfwPollEvents();

	} 
	while (glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(_window) == 0);

	return 0;
}
void Context::Frame()
{

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
}