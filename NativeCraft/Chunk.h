#pragma once

#include "nchfx.h"
#include "VisibilityMesh.h"
#include "FrameTime.h"
#include "Texture.h"

using namespace glm;

class Chunk
{
public:

	Chunk(ivec2 position);
	~Chunk();

	void Render(FrameTime* _frTime);
	void Update(FrameTime* _frTime);

	void UpdateVisibilityMesh();

	unsigned int _data[16][256][16];

	VisibilityMesh* _mesh;

	ivec2 GridPosition;
	mat4x4 World;
};

