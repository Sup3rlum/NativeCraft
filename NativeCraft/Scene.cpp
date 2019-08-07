#include "Scene.h"



Scene::Scene(ContextParameters* params)
{
	_params = params;

	_camera = new Camera();
	_world = new World();
	_rb = new RenderBatch(params);

	_ImmShader = new Shader("./shaders/vert.glsl", "./shaders/geom.glsl", "./shaders/frag.glsl");

}

void Scene::Update(GLFWwindow* _win, FrameTime* _frTime)
{
	_camera->Update(_win, _params, _frTime);
}
void Scene::Render(FrameTime* _frTime)
{

	glClearColor(0.0f, 0.2f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_ImmShader->UseProgram();
	_ImmShader->SetMatrix("Projection", _camera->Projection);
	_ImmShader->SetMatrix("View", _camera->View);
	_ImmShader->SetVector("LightDirection", vec3(-1, -1, -1));

	_world->Render(_ImmShader, _camera, _frTime);
	

}