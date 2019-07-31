#pragma once

#include "nchfx.h"

#include "Block.h"

using namespace glm;
using namespace std;


class VertexBuffer
{
	GLuint _vao;
public:
	VertexBuffer(vector<Block>* _data);
	void Render();

	GLuint primitiveCount;
};


