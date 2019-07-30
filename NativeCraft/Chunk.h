#pragma once

#include "nchfx.h"
#include "VertexBuffer.h"

using namespace glm;

class Chunk
{
public:

	Chunk();
	~Chunk();

	unsigned int _data[16][256][16];

	VertexBuffer* _vBuffer;

	ivec3 GridPosition;
};

