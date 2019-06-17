#ifndef GL_VERTEX_DESCRIPTOR_HPP
#define GL_VERTEX_DESCRIPTOR_HPP

#include "VertexArray.hpp"
#include "VertexArrayBinding.hpp"

#include <GL/glew.h>

namespace GL
{

class VertexDescriptor:
	public VertexArray
{
private:
	VertexArrayBinding binding;
protected:
	void AddAttrib(
		GLuint index,
		GLint size,
		GLenum type,
		bool normalized,
		GLuint relativeOffset
	)
	{
		EnableAttrib(index);
		FormatAttrib(index, size, type, normalized, relativeOffset);
		binding.BindAttrib(*this, index);
	}

	void BindVertexBuffer(const Buffer& buffer, GLintptr offset, GLsizei stride)
	{
		binding.BindBuffer(*this, buffer, offset, stride);
	}
};

} //namespace GL

#endif//GL_VERTEX_DESCRIPTOR_HPP
