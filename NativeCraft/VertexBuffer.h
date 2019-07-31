#pragma once

#include "nchfx.h"

using namespace glm;
using namespace std;


class VertexBuffer
{
	GLuint _vao;
public:
	VertexBuffer(const vec3* _data, int count);
	void Render();

	GLuint primitiveCount;
};

