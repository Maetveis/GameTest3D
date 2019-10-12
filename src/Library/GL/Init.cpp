#include "Init.hpp"

#include <Library/Logger/Logger.hpp>

#include <GL/glew.h>

bool GL::InitGlew()
{
	// Starting Glew
	GLenum error = glewInit();
	if ( error != GLEW_OK )
	{
		Logger::Error() << "Glew Init failed: " << glewGetErrorString(error) << '\n';
		return false;
	}

	Logger::Info() << "Opengl version: " << glGetString(GL_VERSION) << '\n';

	if (!GLEW_EXT_texture_filter_anisotropic)
	{
		Logger::Error() << "Unsupported Required Extension: " << "EXT_texture_filter_anisotropic" << '\n';
		return false; 
	}

	return true;
}
