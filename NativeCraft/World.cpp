#include "World.h"


World::World(GeneratorSettings* _gen)
{
	_shader = new Shader("./shaders/vert.glsl", "./shaders/frag.glsl");

	_texture = new Texture("./textures/atlas.jpg");
	_heightmap = new Texture("./textures/heightmap.png");

	BlockIDTextureManager::Init();

	_genSettings = _gen;


	_loadedChunks = new unordered_map<uint64_t, Chunk*>();

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			(*_loadedChunks)[ncpair(i,j)] = new Chunk(_heightmap, ivec2(i, j));
		}
	}

	for (auto kv : *_loadedChunks)
	{
		kv.second->ComputeVisibility(_loadedChunks);
	}
}

void World::Render(Camera* _camera, FrameTime* _frTime)
{

	_shader->UseProgram();
	_shader->SetMatrix("Projection", _camera->Projection);
	_shader->SetMatrix("View", _camera->View);
	_shader->SetVector("LightDirection", vec3(-1, -1, -1));

	_shader->SetTexture(0, _texture);

	for (auto kv : *_loadedChunks)
	{
		_shader->SetMatrix("World", translate(identity<mat4>(), vec3(kv.second->GridPosition.x * 16, 0, kv.second->GridPosition.y * 16)));
		kv.second->Render(_frTime);
	}

}

void World::Update(FrameTime* _frTime)
{

}
void World::GenerateSpawnArea()
{

}