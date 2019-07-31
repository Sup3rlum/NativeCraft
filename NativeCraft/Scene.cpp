#include "Scene.h"


Scene::Scene()
{
	_camera = new Camera();
	_shader = new Shader("./shaders/vert.glsl", "./shaders/geom.glsl", "./shaders/frag.glsl");
	//_shader = new Shader("./shaders/debug_vert.glsl", "./shaders/debug_frag.glsl");
	_chunk = new Chunk(ivec2(0, 0));

	_texture = new Texture("./textures/dirt.jpg");
}

void Scene::Update(GLFWwindow* _win, ContextParameters* _params, FrameTime* _frTime)
{
	_camera->Update(_win, _params, _frTime);
}
void Scene::Render(FrameTime* _frTime)
{
	_shader->UseProgram();

	_shader->SetMatrix("View", _camera->View);
	_shader->SetMatrix("Projection", _camera->Projection);
	_shader->SetTexture(0, _texture);

	_chunk->Render(_frTime);
}