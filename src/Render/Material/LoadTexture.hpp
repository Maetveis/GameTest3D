#ifndef RENDER_LOAD_TEXTURE_HPP
#define RENDER_LOAD_TEXTURE_HPP

#include <string>

namespace GL
{
class Texture2D;
}

struct SDL_Surface;

namespace Render
{

void LoadImageDataFile(const std::string& fileName, GL::Texture2D& targetTexture);

void LoadImageDataSurface(SDL_Surface*, GL::Texture2D& targetTexture);

} // namespace Render

#endif
