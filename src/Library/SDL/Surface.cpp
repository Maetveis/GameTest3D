#include "Surface.hpp"

#include <SDL2/SDL.h>
#include <utility>

namespace SDL
{

Surface::Surface(SDL_Surface* _sdlSurf) :
	sdlSurf(_sdlSurf)
{
}

Surface::~Surface()
{
}

Surface::Surface(Surface&& lhs) :
	sdlSurf(lhs.sdlSurf.release())
{
}

Surface& Surface::operator= (Surface&& lhs)
{
	std::swap(sdlSurf, lhs.sdlSurf);
	return *this;
}

void Surface::Free::operator() (SDL_Surface* sdlSurf)
{
	SDL_FreeSurface(sdlSurf);
}

} //namespace SDL
