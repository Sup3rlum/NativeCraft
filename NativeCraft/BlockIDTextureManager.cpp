#include "BlockIDTextureManager.h"

vector<vec2> BlockIDTextureManager::_ids;

void BlockIDTextureManager::Init()
{
	// ID 1
	_ids.push_back(vec2(2, 0));
	_ids.push_back(vec2(2, 0));
	_ids.push_back(vec2(2, 0));
	_ids.push_back(vec2(2, 0));
	_ids.push_back(vec2(2, 0));
	_ids.push_back(vec2(2, 0));

	// ID 2

	_ids.push_back(vec2(3, 0));
	_ids.push_back(vec2(3, 0));
	_ids.push_back(vec2(2, 0));
	_ids.push_back(vec2(0, 0));
	_ids.push_back(vec2(3, 0));
	_ids.push_back(vec2(3, 0));

	// ID 3

	_ids.push_back(vec2(2, 1));
	_ids.push_back(vec2(2, 1));
	_ids.push_back(vec2(2, 1));
	_ids.push_back(vec2(2, 1));
	_ids.push_back(vec2(2, 1));
	_ids.push_back(vec2(2, 1));

	// ID 4

	_ids.push_back(vec2(2, 2));
	_ids.push_back(vec2(2, 2));
	_ids.push_back(vec2(2, 2));
	_ids.push_back(vec2(2, 2));
	_ids.push_back(vec2(2, 2));
	_ids.push_back(vec2(2, 2));
}
vec2 BlockIDTextureManager::Get(int id, int sideindex)
{
	return _ids[id * 6 + sideindex];
}
