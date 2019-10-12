#ifndef GL_SHADER_STORAGE_BINDING_HPP
#define GL_SHADER_STORAGE_BINDING_HPP

#include <GL/glew.h>

#include <Library/StaticCounter.hpp>
#include <Library/Logger/Logger.hpp>

namespace GL
{
	class Program;
	class Buffer;
	class Range;
}

namespace GL {

class ShaderStorageBinding
{
private:
	StaticCounter<GLuint, ShaderStorageBinding> bindingIndex;
public:
	ShaderStorageBinding()
	{
		Logger::Debug() << "Created shader storage buffer with binding index: " << bindingIndex.Get() << '\n';
	}

	void AttachToBlock(const Program& program, const GLuint index) const;

	void AttachBuffer(const Buffer& buffer);

	void AttachBufferRange(const Buffer& buffer, GL::Range range);

	GLuint GetBlockBinding() const
	{
		return bindingIndex;
	}
};

} //namespace GL

#endif //GL_SHADER_STORAGE_BINDING_HPP
