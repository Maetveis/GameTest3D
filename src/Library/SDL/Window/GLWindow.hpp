#include <SDL2/SDL_opengl.h>

#include <string>
#include <memory>

struct SDL_Window;
struct SDL_Surface;

using SDL_GLContext = void *;

namespace SDL
{

struct WindowInfo;
class Surface;

class GLWindow
{
private:
	struct FreeContext
	{
		void operator() (SDL_GLContext context);
	};

	struct FreeWindow
	{
		void operator() (SDL_Window* window);
	};

	std::unique_ptr<SDL_Window, FreeWindow> sdlWindow;
	std::unique_ptr<void, FreeContext> sdlContext;
public:
	GLWindow(const WindowInfo& wnd);
	~GLWindow();

	void Present();

	void SetIcon(const SDL::Surface& sdlSurf);
	void SetTitle(const std::string& title);
	void SetPos(int x, int y);
	void SetSize(int w, int h);
	void EnableResize();
	void DisableResize();
	void Show();
	void Hide();
};

} //namespace SDL
