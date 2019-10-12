#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include <GL/glew.h>

#include "Buffer.hpp"

namespace GL {

/*
A Vertex Array describing the attriubtes of each vertex

Can be attached to a vertex array binding point to asssiciate it with buffers
to source the attributes from.
Attaches to an Index Buffer explicitly via AttachIndexBuffer or implicitly to
the currently bound IndexBuffer using the AttribPointer function
*/
class VertexArray
{
protected:
	GLuint id;
public:
	VertexArray()
	{
		glCreateVertexArrays(1, &id);
	}

	~VertexArray()
	{
		glDeleteVertexArrays(1, &id);
	}

	void Bind() const
	{
		glBindVertexArray(id);
	}

	void UnBind() const
	{
		glBindVertexArray(0);
	}

	void BindIndexBuffer(const Buffer& indexBuffer)
	{
		glVertexArrayElementBuffer(id, indexBuffer.GetId());
	}

	void EnableAttrib(GLuint index)
	{
		glEnableVertexArrayAttrib(id, index);
	}

	void FormatAttrib(
		GLuint index,
		GLint size,
		GLenum type,
		bool normalized,
		GLuint relativeOffset
	)
	{
		glVertexArrayAttribFormat(id, index, size, type, normalized, relativeOffset);
	}

	GLint GetId() const
	{
		return id;
	}

	static void AttribPointer(
		GLuint index,
		GLint size,
		GLenum type,
		bool normalized,
		GLuint stride,
		void* offset
	)
	{
		glVertexAttribPointer(index, size, type, normalized, stride, offset);
	}
};

}// namespace GL

#endif //VERTEX_HPP
