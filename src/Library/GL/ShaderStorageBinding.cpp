#include "ShaderStorageBinding.hpp"

#include "Program.hpp"
#include "Buffer.hpp"
#include "Range.hpp"

namespace GL {

void ShaderStorageBinding::AttachBuffer(const Buffer& buffer)
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingIndex, buffer.GetId());
}

void ShaderStorageBinding::AttachBufferRange(const Buffer& buffer, GL::Range range)
{
	glBindBufferRange(GL_SHADER_STORAGE_BUFFER, bindingIndex, buffer.GetId(), range.offset, range.size);
}

void ShaderStorageBinding::AttachToBlock(const Program& program, const GLuint index) const
{
	//Logger::Debug() << "shader storage buffer bind:" << bindingIndex << " -> program" << program.Get() << ":"  << index <<  '\n';

	glShaderStorageBlockBinding(program.Get(), index, bindingIndex);
}

}// namspace GL
