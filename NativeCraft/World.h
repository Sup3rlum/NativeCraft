#pragma once

#include "nchfx.h"

#include "Chunk.h"

using namespace std;

class World
{
public:
	vector<unsigned long> _idTable;

	vector<Chunk>_loadedChunks;
};

