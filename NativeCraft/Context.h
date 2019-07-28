#pragma once



#include "nchfx.h"

using namespace glm;



struct ContextParameters
{
public:
	GLuint contextMajorVersion;
	GLuint contextMinorVersion;
	GLuint contextSampleCount;
	GLuint contextCompatibility;
	GLuint contextProfile;
	GLuint width;
	GLuint height;
};


class Context
{
public:
	static GLFWwindow* _window;
	static ContextParameters* _contextParameters;

	static int Initialize(ContextParameters* _params);
	static void Frame();

	static int InitGLEW();
	static int InitGLFW();

};
