#ifndef VERTEX_ARRAY_DESCRIPTOR_HPP
#define VERTEX_ARRAY_DESCRIPTOR_HPP

#include <GL/glew.h>

class VertexArrayDescriptor
{
private:
	GLuint id;
public:
	VertexArrayDescriptor()
	{
		glCreateVertexArrays(1, &id);
	}

	~VertexArrayDescriptor()
	{
		glDeleteVertexArrays(1, &id);
	}

	void Bind() const
	{
		glBindVertexArray(id);
	}

	GLint Get() const
	{
		return id;
	}
};

#endif //VERTEX_ARRAY_DESCRIPTOR_HPP
