#pragma once


#include "Camera.h"
#include "Shader.h"
#include "Chunk.h"
#include "World.h"
#include "RenderBatch.h"


class Scene
{
public:
	Scene(ContextParameters* params);
	~Scene();

	void Update(GLFWwindow* _win, FrameTime* _frTime);
	void Render(FrameTime* _frTime);

	World* _world;
	Camera* _camera;

	RenderBatch* _rb;

	Texture* _texture;
	Shader* _shader;

	ContextParameters* _params;
};

