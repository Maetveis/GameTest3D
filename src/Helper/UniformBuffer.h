#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H

#include <GL/glew.h>
#include <vector>

#include "StaticCounter.hpp"
#include "../Log/Logger.h"

class UnifromBlockBindingIndexTrait
{
};

class ShaderProgram;
class Buffer;

class UniformBuffer
{
private:
	StaticCounter<GLuint, UnifromBlockBindingIndexTrait> bindingIndex;

public:

	UniformBuffer()
	{
		Logger::Debug << "Created unifrom buffer with binding index: " << bindingIndex.Get() << '\n';
	}

	void AttachToBlock(const ShaderProgram& program, const GLuint index) const;

	void AttachBuffer(const Buffer& buffer);

	void AttachBufferRange(const Buffer& buffer, GLuint offset, GLuint size);

	GLuint GetBlockBinding() const
	{
		return bindingIndex;
	}

};

#endif //UNIFORM_BUFFER_H
