#include "Scene.h"


Scene::Scene(ContextParameters* params)
{
	_params = params;

	_camera = new Camera();

	_shader = new Shader("./shaders/vert.glsl", "./shaders/frag.glsl");



	_texture = new Texture("./textures/dirt.jpg");

	_world = new World();

	_rb = new RenderBatch(params);
}

void Scene::Update(GLFWwindow* _win, FrameTime* _frTime)
{
	_camera->Update(_win, _params, _frTime);
}
void Scene::Render(FrameTime* _frTime)
{

	_world->Render(_camera, _frTime);

	_rb->DrawTexture(_texture, 100, 100, 1280, 720);

}