#include "Scene.h"


inline float lerp(float a, float b, float f)
{
	return a + f * (b - a);
}


Scene::Scene(ContextParameters* params)
{
	_params = params;

	_camera = new Camera();
	_world = new World();
	_rb = new RenderBatch(params);

	_ssaoGeom = new Shader("./shaders/ssao_geom.vert", "./shaders/ssao_geom.frag");
	_ssaoLight = new Shader("./shaders/ssao.vert", "./shaders/ssao_light.frag");
	_ssao = new Shader("./shaders/ssao.vert", "./shaders/ssao.frag");
	_ssaoBlur = new Shader("./shaders/ssao.vert", "./shaders/ssao_blur.frag");

	_ImmShader = new Shader("./shaders/vert.glsl", "./shaders/frag.glsl");

	_mTransforms = ortho(0, 1, 1, 0);

	// -----GBUFFER

	_gBuffer = new FrameBuffer(_params->width, _params->height);

	_gBuffer->Bind();
	{

		_tPosition = new Texture(params->width, params->height, GL_RGB32F, GL_FLOAT, false);
		_tPosition->Bind();
		{
			_tPosition->SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			_tPosition->SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			_tPosition->SetParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			_tPosition->SetParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


			_gBuffer->BindTexture(_tPosition, GL_COLOR_ATTACHMENT0);
		}


		_tNormal = new Texture(params->width, params->height, GL_RGB32F, GL_FLOAT, false);
		_tNormal->Bind();
		{
			_tNormal->SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			_tNormal->SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);


			_gBuffer->BindTexture(_tNormal, GL_COLOR_ATTACHMENT1);
		}

		_tAlbedo = new Texture(params->width, params->height, GL_RGB, GL_UNSIGNED_BYTE, false);
		_tAlbedo->Bind();
		{
			_tAlbedo->SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			_tAlbedo->SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			_gBuffer->BindTexture(_tAlbedo, GL_COLOR_ATTACHMENT2);
		}


		_gBuffer->SetAttachments(attachments, 3);



		glGenRenderbuffers(1, &rboDepth);
		glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, params->width, params->height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
		// finally check if framebuffer is complete
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
	}
	_gBuffer->Unbind();

	//---------- SSAO BUFFER

	_ssaoBuffer = new FrameBuffer(params->width, params->height);
	_ssaoBufferBlur = new FrameBuffer(params->width, params->height);

	_ssaoBuffer->Bind();
	{
		_tSsao = new Texture(params->width, params->height, GL_RED, GL_FLOAT, false);
		_tSsao->SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		_tSsao->SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		_ssaoBuffer->BindTexture(_tSsao, GL_COLOR_ATTACHMENT0);
	}
	_ssaoBuffer->Unbind();

	_ssaoBufferBlur->Bind();
	{
		_tSsaoBlur = new Texture(params->width, params->height, GL_RED, GL_FLOAT, false);
		_tSsaoBlur->SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		_tSsaoBlur->SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		_ssaoBufferBlur->BindTexture(_tSsaoBlur, GL_COLOR_ATTACHMENT0);
	}
	_ssaoBufferBlur->Unbind();

	// generate sample kernel
	// ----------------------
	std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
	std::default_random_engine generator;
	for (unsigned int i = 0; i < 64; ++i)
	{
		glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
		sample = glm::normalize(sample);
		sample *= randomFloats(generator);
		float scale = float(i) / 64.0;

		// scale samples s.t. they're more aligned to center of kernel
		scale = lerp(0.1f, 1.0f, scale * scale);
		sample *= scale;
		ssaoKernel.push_back(sample);
	}

	// generate noise texture
	// ----------------------
	std::vector<glm::vec3> ssaoNoise;
	for (unsigned int i = 0; i < 16; i++)
	{
		glm::vec3 noise(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, 0.0f); // rotate around z-axis (in tangent space)
		ssaoNoise.push_back(noise);
	}

	_noiseTexture = new Texture(4, 4, GL_RGB32F, GL_FLOAT, false);
	_noiseTexture->SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	_noiseTexture->SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	_noiseTexture->SetParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	_noiseTexture->SetParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

	_noiseTexture->SetData(ssaoNoise.data());

	// lighting info
	// -------------
	glm::vec3 lightPos = glm::vec3(2.0, 4.0, -2.0);
	glm::vec3 lightColor = glm::vec3(0.2, 0.2, 0.7);

	// shader configuration
	// --------------------
	_ssaoLight->UseProgram();
	_ssaoLight->SetInt("gPosition", 0);
	_ssaoLight->SetInt("gNormal", 1);
	_ssaoLight->SetInt("gAlbedo", 2);
	_ssaoLight->SetInt("ssao", 3);

	_ssao->UseProgram();
	_ssao->SetInt("gPosition", 0);
	_ssao->SetInt("gNormal", 1);
	_ssao->SetInt("texNoise", 2);

	_ssaoBlur->UseProgram();
	_ssaoBlur->SetInt("ssaoInput", 0);

}

void Scene::Update(GLFWwindow* _win, FrameTime* _frTime)
{
	_camera->Update(_win, _params, _frTime);
}
void Scene::Render(FrameTime* _frTime)
{
/*
	glClearColor(0.0f, 0.2f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_ImmShader->UseProgram();
	_ImmShader->SetMatrix("Projection", _camera->Projection);
	_ImmShader->SetMatrix("View", _camera->View);



	_world->Render(_ImmShader, _camera, _frTime);
	*/

	_gBuffer->Bind();
	{
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_ssaoGeom->UseProgram();
		_ssaoGeom->SetMatrix("Projection", _camera->Projection);
		_ssaoGeom->SetMatrix("View", _camera->View);



		_world->Render(_ssaoGeom, _camera, _frTime);
	}
	_gBuffer->Unbind();
	
	glClearColor(0.0f, 0.2f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*

	_ssaoBuffer->Bind();
	{
		glClear(GL_COLOR_BUFFER_BIT);

		_ssao->UseProgram();
		// Send kernel + rotation 
		for (unsigned int i = 0; i < 64; ++i)
			_ssao->SetVector("samples[" + std::to_string(i) + "]", ssaoKernel[i]);

		_ssao->SetMatrix("projection", _camera->Projection);


		_rb->DrawTextures(3, new Texture * [3]{ _tPosition, _tNormal, _noiseTexture }, 0, 0, 2560, 1440, _mTransforms, _ssao);
	}
	_ssaoBuffer->Unbind();
	

	_ssaoBufferBlur->Bind();
	{
		glClear(GL_COLOR_BUFFER_BIT);
		_ssaoBlur->UseProgram();


		_rb->DrawTextures(1, new Texture * [1]{ _tSsao }, 0, 0, 2560, 1440, _mTransforms, _ssaoBlur);
	}
	_ssaoBufferBlur->Unbind();

	glClearColor(0.0f, 0.3f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_ssaoLight->UseProgram();
	
	_ssaoLight->SetMatrix("View", _camera->View);
	*/

	_rb->DrawTextures(4, new Texture * [4]{ _tPosition, _tNormal, _tAlbedo, _tSsaoBlur }, 0, 0, 2560, 1440, _mTransforms, _ssaoLight);

	_rb->DrawTexture(_tSsaoBlur, 0, 0, 100, 100);
	_rb->DrawTexture(_tPosition, 100, 0, 100, 100);
	_rb->DrawTexture(_tNormal, 200, 0, 100, 100);
	_rb->DrawTexture(_tAlbedo, 300, 0, 100, 100);

}