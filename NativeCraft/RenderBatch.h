#pragma once

#include "nchfx.h"
#include "Texture.h"
#include "ContextParameters.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "Vertex.h"

using namespace glm;
using namespace std;

class RenderBatch
{

public:
	RenderBatch(ContextParameters* _context);

	void DrawTexture(Texture* _tex, float x, float y, float width, float height);


	Shader* _shader;
	VertexBuffer* _vb;

	mat4x4 View;
};

