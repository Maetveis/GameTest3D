#include "Init.hpp"

#include "../Logger/Logger.hpp"

#include <SDL2/SDL.h>

namespace SDL
{

bool Init()
{
	//Initializing SDL
	if(SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) < 0)
	{
		Logger::Error() << "Couldn't initialize SDL: " << SDL_GetError() << '\n';
		return false;
	}

	return true;
}

bool InitGLContext()
{
	// Setting up SDL_OPENGL Attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	// Color buffers size
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	// Double-buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Depth-buffer size
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Anti-aliasing
	// SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	// SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	// V-sync on
	SDL_GL_SetSwapInterval(1);

	return true;
}

} //namespace SDL
