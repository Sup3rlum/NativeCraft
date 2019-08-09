#pragma once

#include "nchfx.h"
#include "FrameTime.h"
#include "Texture.h"
#include "BoundingBox.h"
#include "VertexBuffer.h"
#include "Vertex.h"
#include "BlockIDTextureManager.h"

using namespace glm;
using namespace std;



class Chunk;

typedef unordered_map<uint64_t, Chunk*> level_map;

class Chunk
{

public:

	Chunk(Texture* _height, ivec2 position);

	void Render(FrameTime* _frTime);
	void Update(FrameTime* _frTime);

	void ComputeVisibility(level_map* _map);
	void AddSide(int sideIndex, vec3 offset, int textureIndex);


	unsigned int _data[16][256][16];

	ivec2 GridPosition;
	mat4x4 World;

	BoundingBox _box;


	// Visibility mesh

	vector<VertexNormalTexture> _vData;
	vector<unsigned int> _iData;
	VertexBuffer* _vBuffer;
};
