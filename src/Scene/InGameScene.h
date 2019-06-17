#ifndef IN_GAME_SCENE_H
#define IN_GAME_SCENE_H

#include "Scene.h"

#include "../Render/Renderer/ObjectRenderer.hpp"
#include "../Render/Scene/Scene.hpp"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

class InGameScene :
	public Scene
{
public:
	InGameScene():
		scene(),
		renderer(scene)
	{
	}

	virtual bool Begin();

	virtual void End();

	virtual void Pause();

	virtual void PrepareRender();
	virtual void Render();

	virtual void Update(double);

	virtual void OnKeyboard(SDL_KeyboardEvent& event);

	virtual void OnWindow(SDL_WindowEvent& event);

	virtual void OnQuit(SDL_QuitEvent& event);

	void Quit();
protected:
private:
	bool LoadData();
	bool LoadShaders();

	Render::Scene scene;
	Render::ObjectRenderer renderer;
};

#endif //IN_GAME_SCENE_H
