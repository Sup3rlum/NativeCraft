#include "World.h"


World::World()
{
	_shader = new Shader("./shaders/vert.glsl", "./shaders/frag.glsl");

	_texture = new Texture("./textures/dirt.jpg");
	_heightmap = new Texture("./textures/heightmap.png");


	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			_loadedChunks.push_back(new Chunk(_heightmap, vec2(i, j)));
		}
	}

}

void World::Render(Shader* _shader, Camera* _camera, FrameTime* _frTime)
{

	_cf = new Frustum(_camera->Projection * _camera->View);

	_shader->SetTexture(0, _texture);

	for (int i = 0; i < _loadedChunks.size(); i++)
	{
		if (_cf->Contains(_loadedChunks[i]->_box))
		{
			_shader->SetMatrix("World", translate(identity<mat4>(), vec3(_loadedChunks[i]->GridPosition.x * 16, 0, _loadedChunks[i]->GridPosition.y * 16)));
			_loadedChunks[i]->Render(_frTime);
		}
	}

}

void World::Update(FrameTime* _frTime)
{

}