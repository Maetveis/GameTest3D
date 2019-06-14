#include "Init.hpp"

#include "../../Library/Logger/Logger.hpp"

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

	return true;
}
