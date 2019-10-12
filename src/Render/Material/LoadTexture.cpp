#include "LoadTexture.hpp"

#include <Library/GL/Texture/Texture2D.hpp>
#include <Library/Logger/Logger.hpp>

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace Render
{

void LoadImageDataFile(const std::string& fileName, GL::Texture2D& targetTexture)
{
	SDL_Surface* surface = IMG_Load(fileName.c_str());
	if(surface == nullptr)
	{
		Logger::Error() << "Failed to load Image: " << fileName << '\n';
		return;
	}

	LoadImageDataSurface(surface, targetTexture);
	SDL_FreeSurface(surface);
}

void LoadImageDataSurface(SDL_Surface* surface, GL::Texture2D& targetTexture)
{
	GLenum sourceColorMode;
	GLenum textColorMode;

	if (surface->format->BytesPerPixel == 4)
	{
		textColorMode = GL_RGBA16F;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
		sourceColorMode = GL_RGBA;
#else
		sourceColorMode = GL_BGRA;
#endif
	}
	else
	{
		textColorMode = GL_R11F_G11F_B10F;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
		sourceColorMode = GL_RGB;
#else
		sourceColorMode = GL_BGR;
#endif
	}

	targetTexture.SetStorage(11, textColorMode, surface->w, surface->h);
	targetTexture.SubImageData(
		0, 0, 0, surface->w, surface->h, sourceColorMode,
		GL_UNSIGNED_BYTE, surface->pixels
	);
}

} // namespace Render
