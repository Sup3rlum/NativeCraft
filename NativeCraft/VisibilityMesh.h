#pragma once

#include "nchfx.h"
#include "VertexBuffer.h"
#include "Vertex.h"

using namespace glm;
using namespace std;

class VisibilityMesh
{
public:

	VisibilityMesh();
	~VisibilityMesh();

	void Compute(unsigned int data[16][256][16]);
	void Modify();

	void AddSide(int sideIndex, vec3 offset);

	void Render();

	vector<Vertex> _vData;
	vector<unsigned int> _iData;


	GLuint meshSize;

	VertexBuffer* _vBuffer;
};

