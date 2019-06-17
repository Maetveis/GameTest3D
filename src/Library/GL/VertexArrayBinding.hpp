#ifndef VERTEX_ARRAY_BINDING
#define VERTEX_ARRAY_BINDING

#include "VertexArray.hpp"

#include "../StaticCounter.hpp"

#include <GL/glew.h>

namespace GL {

/*
A Binding point for connecting multiple vertex attributes to a single buffer
*/
class VertexArrayBinding
{
private:
	StaticCounter<GLuint, VertexArrayBinding> binding;
public:
	/*
	Attach an attribute with a given index of a vertexarray to this binding point
	*/
	inline void BindAttrib(const VertexArray& va, GLuint attribIndex)
	{
		glVertexArrayAttribBinding(va.GetId(), attribIndex, binding);
	}

	/*
	Attach a buffer to this binding point
	*/
	inline void BindBuffer(const VertexArray& va, const Buffer& buffer, GLintptr offset, GLsizei stride)
	{
		glVertexArrayVertexBuffer(va.GetId(), binding, buffer.GetId(), offset, stride); // Check this line if it doesnt work
	}
};

} //namespace GL

#endif //VERTEX_ARRAY_BINDING
