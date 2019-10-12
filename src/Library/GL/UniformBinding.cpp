#include "UniformBinding.hpp"

#include "Program.hpp"
#include "Buffer.hpp"

namespace GL {

void UniformBinding::AttachBuffer(const Buffer& buffer) const
{
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffer.GetId());
}

void UniformBinding::AttachBufferRange(const Buffer &buffer, Range range) const
{
	glBindBufferRange(GL_UNIFORM_BUFFER, bindingPoint, buffer.GetId(), range.offset, range.size);
}

void UniformBinding::AttachToBlock(const Program& program, const GLuint index) const
{
	Logger::Debug() << "Uniform buffer bind: programIndex " << index << " -> bindingPoint " << bindingPoint <<  "\n";

	glUniformBlockBinding(program.Get(), index, bindingPoint);
}

}// namspace GL
