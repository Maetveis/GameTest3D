#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>

struct SDL_Surface;

class Texture
{
public:
	Texture()
	{
	}

	explicit Texture(GLenum target)
	{
		CreateName(target);
	}

	Texture(GLenum target, const SDL_Surface* surface) :
		Texture(target)
	{
		FromSurface(surface);
	}

	Texture(GLenum target, const std::string fileName)
	{
		FromFile(target, fileName);
	}

	Texture(const Texture&) = delete;

	Texture& operator=(const Texture&) = delete;

	void FromFile(GLenum target, const std::string fileName);

	void FromSurface(const SDL_Surface* surface, GLint level = 0);

	void SetMinFilter(GLenum filter)
	{
		glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, filter);
	}

	void SetMagFilter(GLenum filter)
	{
		glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, filter);
	}

	void GenerateMipmap()
	{
		glGenerateTextureMipmap(textureID);
	}

	void SetName(GLuint name)
	{
		textureID = name;
	}

	GLuint GetName() const
	{
		return textureID;
	}

	void CreateName(GLenum target)
	{
		glCreateTextures(target, 1, &textureID);
	}

	void Bind(GLuint unit)
	{
		glBindTextureUnit(GL_TEXTURE0 + unit, textureID);
	}

	~Texture()
	{
		glDeleteTextures(1, &textureID);
	}
private:
	GLuint textureID;
};

#endif //TEXTURE_H
