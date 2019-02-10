#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H

#include <GL/glew.h>
#include <vector>

#include "StaticCounter.hpp"
#include "Buffer.hpp"
#include "../Log/Logger.h"

class UnifromBlockBindingIndexTrait
{
};

class ShaderProgram;
class UniformBuffer
{
private:
	StaticCounter<GLuint, UnifromBlockBindingIndexTrait> bindingIndex;

	Buffer uniformBuffer;

public:

	UniformBuffer()
	{
		Logger::Debug << "Created unifrom buffer with binding index: " << bindingIndex.Get() << '\n';
	}

	void BufferData(const GLuint bytes, void const* data, const GLenum usage);

	template<typename T>
	void BufferData(const T& data, const GLenum usage)
	{
		BufferData(sizeof(data), reinterpret_cast<void const *>(&data), usage);
	}

	template<typename T>
	void BufferData(const std::vector<T>& data, const GLenum usage)
	{
		BufferData(sizeof(T) * data.size(), reinterpret_cast<void const*>(data.data()), usage);
	}

	void Bind(const ShaderProgram& program, const GLuint index) const;

	GLuint GetBlockBinding() const
	{
		return bindingIndex;
	}

	GLuint GetBufferID() const
	{
		return uniformBuffer.GetId();
	}

};

#endif //UNIFORM_BUFFER_H
