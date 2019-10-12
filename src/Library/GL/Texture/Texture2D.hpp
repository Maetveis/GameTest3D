#ifndef GL_TEXTURE_2D_HPP
#define GL_TEXTURE_2D_HPP

#include "Texture.hpp"

namespace GL
{

class Texture2D : public Texture
{
public:
	Texture2D() :
		Texture(GL_TEXTURE_2D)
	{
	}

	void SetStorage(GLuint levels, GLenum colorFormat, GLint width, GLint height)
	{
		glTextureStorage2D(textureID, levels, colorFormat, width, height);
	}

	void SubImageData(
		GLint level,
		GLuint xOffset,
		GLuint yOffset,
		GLuint width,
		GLuint height,
		GLenum sourcePixelMode,
		GLenum sourcePixelFormat,
		void* sourcePixels
	)
	{
		glTextureSubImage2D(
			textureID,
			level,
			xOffset,
			yOffset,
			width,
			height,
			sourcePixelMode,
			sourcePixelFormat,
			sourcePixels
		);
	}
};

} // namespace GL

#endif //GL_TEXTURE_2D_HPP
