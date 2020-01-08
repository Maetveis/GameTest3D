#include "GLWindow.hpp"
#include "WindowInfo.h"

#include "Library/SDL/Surface.hpp"

#include <SDL2/SDL.h>

namespace SDL
{

GLWindow::GLWindow(const WindowInfo& wnd) :
	sdlWindow(SDL_CreateWindow(wnd.title.c_str(), wnd.x, wnd.y, wnd.w, wnd.h, wnd.flags | SDL_WINDOW_OPENGL)),
	sdlContext(SDL_GL_CreateContext(sdlWindow.get()))
{
}

GLWindow::~GLWindow()
{
}

void GLWindow::FreeContext::operator() (SDL_GLContext context)
{
	SDL_GL_DeleteContext(context);
}

void GLWindow::FreeWindow::operator() (SDL_Window* window)
{
	SDL_DestroyWindow(window);
}

void GLWindow::Present()
{
	SDL_GL_SwapWindow(sdlWindow.get());
}

void GLWindow::SetIcon(const SDL::Surface& sdlSurf)
{
	SDL_SetWindowIcon(sdlWindow.get(), sdlSurf.Get());
}

void GLWindow::SetTitle(const std::string& title)
{
	SDL_SetWindowTitle(sdlWindow.get(), title.c_str());
}

void GLWindow::SetPos(int x, int y)
{
	SDL_SetWindowPosition(sdlWindow.get(), x, y);
}

void GLWindow::SetSize(int w, int h)
{
	SDL_SetWindowSize(sdlWindow.get(), w, h);
}

void GLWindow::EnableResize()
{
	SDL_SetWindowResizable(sdlWindow.get(), SDL_TRUE);
}

void GLWindow::DisableResize()
{
	SDL_SetWindowResizable(sdlWindow.get(), SDL_FALSE);
}

void GLWindow::Show()
{
	SDL_ShowWindow(sdlWindow.get());
}

void GLWindow::Hide()
{
	SDL_HideWindow(sdlWindow.get());
}

} //namespace SDL
