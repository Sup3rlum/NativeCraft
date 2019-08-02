#pragma once


#include "Camera.h"
#include "Shader.h"
#include "Chunk.h"
#include "World.h"

class Scene
{
public:
	Scene();
	~Scene();

	void Update(GLFWwindow* _win, ContextParameters* _params, FrameTime* _frTime);
	void Render(FrameTime* _frTime);

	World* _world;
	Camera* _camera;
	Chunk* _chunk;

	Texture* _texture;
	Shader* _shader;
};

