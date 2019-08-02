#pragma once

#include "nchfx.h"
#include "VisibilityMesh.h"
#include "FrameTime.h"
#include "Texture.h"

using namespace glm;

class Chunk
{
public:

	Chunk(Texture* _height, vec2 position);

	void Render(FrameTime* _frTime);
	void Update(FrameTime* _frTime);

	void UpdateVisibilityMesh();

	unsigned int _data[16][256][16];

	VisibilityMesh* _mesh;

	vec2 GridPosition;
	mat4x4 World;
};

