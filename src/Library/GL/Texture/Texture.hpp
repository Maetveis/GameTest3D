#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <string>

namespace GL {

class Texture
{
protected:
	GLuint textureID;

public:
	explicit Texture(GLenum target)
	{
		glCreateTextures(target, 1, &textureID);
	}

	Texture(const Texture&) = delete;

	Texture& operator=(const Texture&) = delete;

	Texture(Texture&& other) :
		textureID(other.textureID)
	{
		other.textureID = 0;
	}

	Texture& operator=(Texture&& other)
	{
		std::swap(textureID, other.textureID);
		return *this;
	}

	void SetMinFilter(GLenum filter)
	{
		glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, filter);
	}

	void SetMagFilter(GLenum filter)
	{
		glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, filter);
	}

	void SetAnisotropy(GLfloat max)
	{
		glTextureParameterf(textureID, GL_TEXTURE_MAX_ANISOTROPY, max);
	}

	void GenerateMipmap()
	{
		glGenerateTextureMipmap(textureID);
	}

	GLuint GetId() const
	{
		return textureID;
	}

	void Bind(GLuint unit)
	{
		glBindTextureUnit(unit, textureID);
	}

	virtual ~Texture()
	{
		if(textureID != 0)
			glDeleteTextures(1, &textureID);
	}

	static GLfloat GetMaxAnisotropy()
	{
		GLfloat ret;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &ret);

		return ret;
	}
};

} //namespace GL

#endif //TEXTURE_HPP
