#include "ScaledDeltaTimer.h"
#include "../Scene/SceneManager.h"

namespace SDL
{
	class GLWindow;
}

class Game
{
public:
	Game();
	~Game();
	void Run();

	bool running;
protected:
private:
	bool Init();
	void HandleEvents();
	void Update();
	void Render();
	void Destroy();
	void DelayFrameTime(const unsigned frameStart, const unsigned short targetFPS);

	SceneManager sceneManager;
	std::unique_ptr<SDL::GLWindow> mainWindow;
	ScaledDeltaTimer timer;
	unsigned short targetFPS = 60;
};
