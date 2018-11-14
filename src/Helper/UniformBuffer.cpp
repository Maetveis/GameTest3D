#include "UniformBuffer.h"

#include "ShaderProgram.h"

unsigned UniformBuffer::initCount = 0;

void UniformBuffer::Init()
{
	binding = initCount++;
	glGenBuffers(1, &uniformBufferID);
	//glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBufferID);
}

void UniformBuffer::BufferData(GLuint bytes, const void* data, GLenum usage)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, binding, uniformBufferID);
	glBufferData(GL_UNIFORM_BUFFER, bytes, data, usage);
}

void UniformBuffer::Bind(const ShaderProgram& program, const GLuint index) const
{
	glUniformBlockBinding(program.Get(), index, binding);
}

void UniformBuffer::Destroy()
{
	glDeleteBuffers(1, &uniformBufferID);
}
