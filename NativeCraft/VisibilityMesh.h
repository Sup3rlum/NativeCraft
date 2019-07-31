#pragma once

#include "nchfx.h"
#include "VertexBuffer.h"

using namespace glm;
using namespace std;

class VisibilityMesh
{
public:

	VisibilityMesh();
	~VisibilityMesh();

	void Compute(/*const int*** data*/);
	void Modify();

	vector<vec3> _positions;
	vector<vec3> _sides;

	GLuint meshSize;

	VertexBuffer* _vBuffer;
};

