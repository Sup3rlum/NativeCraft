#pragma once

#include "nchfx.h"
#include "stb_image.h"

class Texture
{
public:

	Texture(const char* filepath);

	GLuint _handle;

	unsigned char* _dataInternal;
};

