#pragma once

#include "nchfx.h"

#include "Chunk.h"
#include "FrameTime.h"
#include "Shader.h"
#include "Camera.h"
#include "Frustum.h"

using namespace std;

class World
{
public:
	World();

	vector<unsigned long> _idTable;

	vector<Chunk*>_loadedChunks;

	Shader* _shader;
	Texture* _texture;
	Texture* _heightmap;

	Chunk* _chunk;

	Frustum* _cf;

	void Render(Shader* _shader, Camera* _camera, FrameTime* _frTime);
	void Update(FrameTime* _frTime);
};

