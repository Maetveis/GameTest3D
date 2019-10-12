#ifndef GL_UNIFORM_BINDING_HPP
#define GL_UNIFORM_BINDING_HPP

#include "Range.hpp"

#include <Library/StaticCounter.hpp>
#include <Library/Logger/Logger.hpp>

#include <GL/glew.h>
#include <vector>

namespace GL {

class Program;
class Buffer;

}

namespace GL {

class UniformBinding
{
private:
	StaticCounter<GLuint, UniformBinding> bindingPoint;
public:

	UniformBinding()
	{
		Logger::Debug() << "Created uniform binding bound to: " << bindingPoint << '\n';
	}

	void AttachToBlock(const Program& program, const GLuint index) const;

	void AttachBuffer(const Buffer& buffer) const;

	void AttachBufferRange(const Buffer& buffer, Range range) const;

	GLuint GetBlockBinding() const
	{
		return bindingPoint;
	}

};

}// namespace GL

#endif //GL_UNIFORM_BINDING_HPP