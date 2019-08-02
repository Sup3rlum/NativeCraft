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


	Shader* _ssaoGeom;
	Shader* _ssaoLight;
	Shader* _ssao;
	Shader* _ssaoBlur;

	ContextParameters* _params;





	unsigned int ssaoFBO, ssaoBlurFBO;
	unsigned int ssaoColorBuffer, ssaoColorBufferBlur;
	unsigned int rboDepth;
	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	unsigned int gPosition, gNormal, gAlbedo;
	unsigned int gBuffer;

	unsigned int noiseTexture; 

	vector<glm::vec3> ssaoKernel;
};

