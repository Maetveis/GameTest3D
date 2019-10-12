#ifndef RENDER_LINEAR_BUFFER_HPP
#define RENDER_LINEAR_BUFFER_HPP

#include "LinearCapacity.hpp"

#include <Library/GL/Buffer.hpp>

#include <optional>

namespace Render
{

class LinearBuffer
{
private:
	GL::Buffer buffer;
	LinearCapacity capacity;
public:
	LinearBuffer(uint32_t _capacity, GLenum usage) :
		buffer(),
		capacity(_capacity)
	{
		buffer.InitEmpty(_capacity, usage);
	}

	std::optional<GLuint> PushAligned(GLuint length, void const * data, GLuint alignment)
	{
		auto offset = capacity.AllocateAlligned(length, alignment);
		if(offset.has_value())
		{
			buffer.BufferSubData(*offset, length, data);
		}
		return offset;
	}

	std::optional<GLuint> Push(GLuint length, void const * data)
	{
		auto offset = capacity.Allocate(length);
		if(offset.has_value())
		{
			buffer.BufferSubData(*offset, length, data);
		}
		return offset;
	}

	template <typename T>
	std::optional<GLuint> PushAligned(const T& data, GLuint alignment)
	{
		return PushAligned(sizeof(data), static_cast<void*>(&data), alignment);
	}

	template <typename T>
	std::optional<GLuint> Push(const T& data)
	{
		return Push(sizeof(data), reinterpret_cast<void const*>(&data));
	}

	template <typename T>
	std::optional<GLuint> PushAligned(const std::vector<T>& data, GLuint alignment)
	{
		return PushAligned(sizeof(data.first()) * data.size(), static_cast<void*>(data.data()), alignment);
	}

	template <typename T>
	std::optional<GLuint> Push(const std::vector<T>& data)
	{
		return Push(sizeof(data.front()) * data.size(), reinterpret_cast<void const*>(data.data()));
	}

	GLuint GetCapacity() const
	{
		return capacity.GetCapacity();
	}

	GLuint GetSize() const
	{
		return capacity.GetSize();
	}

	GLuint GetCapacityLeft() const
	{
		return capacity.GetCapacityLeft();
	}

	const GL::Buffer& GetBuffer() const
	{
		return buffer;
	}
};

} //namespace Render

#endif //RENDER_LINEAR_BUFFER_HPP
