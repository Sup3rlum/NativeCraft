#include "Scene.h"



Scene::Scene(ContextParameters* params)
{
	_params = params;

	GeneratorSettings* _set = new GeneratorSettings();

	_set->Seed = 0;

	_camera = new Camera();
	_world = new World(_set);
	_rb = new RenderBatch(params);


	DebugView::Init();

}

void Scene::Update(GLFWwindow* _win, FrameTime* _frTime)
{
	_camera->Update(_win, _params, _frTime);
}
void Scene::Render(FrameTime* _frTime)
{

	glClearColor(0.0f, 0.2f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	_world->Render(_camera, _frTime);
	
	DebugView::Draw(_camera);
}