#include "UniformBuffer.h"

#include "ShaderProgram.h"

void UniformBuffer::BufferData(GLuint bytes, void const* data, GLenum usage)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, uniformBuffer.GetId());
	glBufferData(GL_UNIFORM_BUFFER, bytes, data, usage);
}

void UniformBuffer::Bind(const ShaderProgram& program, const GLuint index) const
{
	Logger::Debug << "unform buffer bind:" << index << " -> " << bindingIndex <<  '\n';

	glUniformBlockBinding(program.Get(), index, bindingIndex);
}
