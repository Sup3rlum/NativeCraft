#pragma once

#include "nchfx.h"

#include "Chunk.h"
#include "FrameTime.h"
#include "Shader.h"
#include "Camera.h"
#include "Frustum.h"
#include "BlockIDTextureManager.h"
#include "GeneratorSettings.h"

using namespace std;

class World
{
public:
	World(GeneratorSettings* _gen);


	unordered_map<uint64_t, Chunk*>* _loadedChunks;

	Shader* _shader;
	Texture* _texture;
	Texture* _heightmap;

	GeneratorSettings* _genSettings;

	void Render(Camera* _camera, FrameTime* _frTime);
	void Update(FrameTime* _frTime);
	void GenerateSpawnArea();
};

