#ifndef IN_GAME_SCENE_H
#define IN_GAME_SCENE_H

#include "Scene.h"
#include "../Manager/ModelManager.h"
#include "../Program/Mesh3DColor.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

class InGameScene :
	public Scene
{
public:
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

	GLuint modelID;

	/*ShaderManager shaderManager;*/
	ModelManager modelManager;

	glm::mat4 matModel;

	Mesh3DColor program;

	/*FrameParams frame;
	LightParams light;*/

	float time;
};

#endif //IN_GAME_SCENE_H
