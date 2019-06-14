#include <memory>
struct SDL_Surface;

namespace SDL
{

class Surface
{
private:
	struct Free
	{
		void operator() (SDL_Surface* sdlSurf);
	};

	std::unique_ptr<SDL_Surface, Free> sdlSurf;
public:
	Surface(SDL_Surface* sdlSurf);

	Surface(const Surface&) = delete;
	Surface& operator= (const Surface&) = delete;

	Surface(Surface&& lhs);
	Surface& operator=(Surface&& lhs);

	SDL_Surface* Get()
	{
		return sdlSurf.get();
	}

	SDL_Surface* const Get() const
	{
		return sdlSurf.get();
	}

	operator SDL_Surface* ()
	{
		return sdlSurf.get();
	}

	operator SDL_Surface* const ()
	{
		return sdlSurf.get();
	}

	~Surface();
};

} //namespace SDL
