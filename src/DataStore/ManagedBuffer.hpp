#ifndef MANAGED_BUFFER_HPP
#define MANAGED_BUFFER_HPP

#include "GPUAllocator.hpp"

#include <Library/GL/Buffer.hpp>
#include <Library/GL/Range.hpp>

class ManagedBuffer
{
private:
	GPUAllocator allocator;
	GL::Buffer buffer;
public:
	ManagedBuffer(GLuint size, GLenum usage) :
		allocator(size)
	{
		buffer.BufferData(size, nullptr, usage);
	}

	GL::Range Reserve(GLuint size, GLuint alignment)
	{
		GL::Range range = Allocate(size, alignment);
		buffer.BufferSubData(range.offset, range.size, nullptr);

		return range;
	}

	GL::Range Push(GLuint size, void const * data, GLuint alignment)
	{
		GL::Range range = Allocate(size, alignment);
		buffer.BufferSubData(range.offset, range.size, data);

		return range;
	}

	template <typename T>
	GL::Range Push(const T& data, GLuint alignment)
	{
		return Push(sizeof(data), &data, alignment);
	}

	template <typename T>
	GL::Range Push(const std::vector<T>& data, GLuint alignment)
	{
		return Push(sizeof(data[0]) * data.size(), data.data(), alignment);
	}

	GL::Range Allocate(GLuint size, GLuint alignment)
	{
		return allocator.Allocate(size, alignment);
	}

	void Free(GL::Range range)
	{
		allocator.DeAllocate(range);
	}

	GL::Buffer& GetBuffer()
	{
		return buffer;
	}

	const GL::Buffer& GetBuffer() const
	{
		return buffer;
	}

	operator GL::Buffer& ()
	{
		return buffer;
	}

	operator const GL::Buffer& () const
	{
		return buffer;
	}
};

#endif
