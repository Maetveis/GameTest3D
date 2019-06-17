#include "InGameScene.h"

#include "../Library/Logger/Logger.hpp"
#include "../Game/Game.h"
#include "../Library/GL/UniformBinding.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include <cmath>

bool InGameScene::Begin()
{
	if(!LoadShaders())
	{
		Logger::Error() << "Failed to load Shaders" << '\n';
		return false;
	}

	if(!LoadData())
	{
		Logger::Error() << "Loading data failed" << '\n';
		return false;
	}

	Logger::Info() << "RenderManager.Init() finished succesfully" << '\n'; //std::endl;

	return true;
}

bool InGameScene::LoadData()
{
	scene.AddObject("../assets/cube.obj", glm::rotate(0.f, glm::vec3(1.f, 0.f, 0.f)));
	scene.AddObject("../assets/alfa.obj", glm::rotate(0.f, glm::vec3(1.f, 0.f, 0.f)));

	return true;
}

bool InGameScene::LoadShaders()
{
	scene.SetProj(glm::perspective(45.0f, 1000/1000.0f, 0.01f, 500.0f));
	scene.SetView(glm::lookAt(glm::vec3( 0.f,  1.f,  6.f), glm::vec3( 0,  0,  0), glm::vec3( 0,  1,  0)));

	scene.AddLight(Render::Light(glm::vec3(0., 0., 1.), glm::vec3(.8, .7, .6), 30));

	scene.Update();

	return true;
}

void InGameScene::Update(double deltaTime)
{
}

void InGameScene::End()
{
}

void InGameScene::Pause()
{
}

void InGameScene::PrepareRender()
{
}

void InGameScene::Render()
{
	renderer.Render();
}

void InGameScene::OnQuit(SDL_QuitEvent& event)
{
	Quit();
}

void InGameScene::OnWindow(SDL_WindowEvent& event)
{
	switch(event.event)
	{
		case SDL_WINDOWEVENT_RESIZED:
			renderer.ResizeViewPort(event.data1, event.data2);
			scene.SetProj(glm::perspective(45.0f, event.data1 / static_cast<float>(event.data2), 0.01f, 500.0f));
		default:
			break;
	}
}

void InGameScene::Quit()
{
	Logger::Debug() << "Exit" << '\n';
	game->running = false;
}
void InGameScene::OnKeyboard(SDL_KeyboardEvent& event)
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE:
			Quit();
			break;
		default:
			Logger::Debug() << "Pressed key with code: " << event.keysym.sym << '\n';
			break;
	}
}
