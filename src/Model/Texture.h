#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Log/Logger.h"

class Texture
{
public:
	void Init(GLenum target)
	{
		glCreateTextures(target, 1, &textureID);
	}
	
	void FromFile(const char* fileName, GLenum target)
	{
		Init(target);
		
		SDL_Surface* loaded_img = IMG_Load(filename);
		if(loaded_img == nullptr)
		{
			Logger::Error << "Failed to load Image: " << filename << '\n';
			return;
		}
		Glint img_mode = 0;
		
		#if SDL_BYTEORDER == SDL_LIL_ENDIAN
		if (loaded_img->format->BytesPerPixel == 4)
			img_mode = GL_RGBA;
		else
			img_mode = GL_RGB;
		#else
		if (loaded_img->format->BytesPerPixel == 4)
			img_mode = GL_BGRA;
		else
			img_mode = GL_BGR;
		#endif
		
		//glActiveTexture(GL_TEXTURE0);
		glTextureStorage2D(textureID, 1, GL_RGBA, loaded_img->w, loaded_img->h);
		
		glTextureSubImage2D(textureID, 0, 0, 0, loaded_img->w, loaded_img->h, img_mode, GL_UNSIGNED_BYTE, loaded_img->pixels);
	}
	
	void Bind(GLuint unit)
	{
		glBindTextureUnit(GL_TEXTURE0 + unit, texture);
	}
	
	~Texture()
	{
		glDeleteTextures(1, &textureID);
	}
private:
	GLuint textureID;
};

#endif //TEXTURE_H