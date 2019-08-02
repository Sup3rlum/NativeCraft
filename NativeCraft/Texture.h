#pragma once

#include "nchfx.h"
#include "stb_image.h"

using namespace glm;

class Texture
{
public:

	Texture(const char* filepath);

	GLuint _handle;

	unsigned char* _dataInternal;

	int _width;
	int _height;
	int _channels;

	vec4 GetData(int w, int h);
};

