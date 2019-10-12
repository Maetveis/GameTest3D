#ifndef RENDER_LINEAR_ALLOCATOR_HPP
#define RENDER_LINEAR_ALLOCATOR_HPP

#include <GL/glew.h>

#include <cstdint>
#include <optional>

namespace Render
{

class LinearCapacity
{
private:
	const GLuint capacity;
	GLuint used;
public:

	LinearCapacity(GLuint _capacity) :
		capacity(_capacity),
		used(0)
	{
	}

	std::optional<GLuint> AllocateAlligned(GLuint length, GLuint alignment)
	{
		GLuint alignedOffset = used + (alignment - (used % alignment)) % alignment;

		if(alignedOffset + length < capacity)
		{
			auto offset = used;
			used = alignedOffset + length;
			return std::make_optional(offset);
		} else {
			return std::nullopt;
		}
	}

	std::optional<GLuint> Allocate(GLuint length)
	{
		if(used + length < capacity)
		{
			auto offset = used;
			used += length;
			return std::make_optional(offset);
		} else {
			return std::nullopt;
		}
	}

	GLuint GetCapacity() const
	{
		return capacity;
	}

	GLuint GetSize() const
	{
		return used;
	}

	GLuint GetCapacityLeft() const
	{
		return capacity - used;
	}

};

} //namespace Render

#endif //RENDER_LINEAR_ALLOCATOR_HPP
