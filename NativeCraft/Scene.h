#pragma once


#include "Camera.h"
#include "Shader.h"
#include "Chunk.h"

class Scene
{
public:
	Scene();
	~Scene();

	void Update(GLFWwindow* _win, ContextParameters* _params, FrameTime* _frTime);
	void Render(FrameTime* _frTime);

	Shader* _shader;
	Chunk* _chunk;
	Camera* _camera;
	Texture* _texture;
};

