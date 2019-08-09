#pragma once

#include "nchfx.h"

using namespace glm;
using namespace std;

class BlockIDTextureManager
{
public:
	static vector<vec2> _ids;

	static void Init();
	static vec2 Get(int _id, int side);
};

