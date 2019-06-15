#ifndef GPU_ALLOCATOR_HPP
#define GPU_ALLOCATOR_HPP

#include "../Library/GL/Range.hpp"

#include <GL/glew.h>
#include <set>

struct BufferOutOfMemoryException
{
};

class GPUAllocator
{
private:
	GLuint max;

	struct ByOffset
	{
		inline bool operator()(const GL::Range& lhs, const GL::Range& rhs) const
		{
			return lhs.offset < rhs.offset;
		}
	};

	struct ByLength
	{
		inline bool operator()(const GL::Range& lhs, const GL::Range& rhs) const
		{
			return lhs.size < rhs.size;
		}
	};

	std::set<GL::Range, ByOffset> holesByOffset;
	std::set<GL::Range, ByLength> holesByLength;

	void AddHole(GLuint offset, GLuint size);
public:
	GPUAllocator(GLuint max);
	~GPUAllocator();

	GL::Range Allocate(GLuint size, GLuint alignment);
	void DeAllocate(GL::Range place);

	GLuint GetSize() const
	{
		return max;
	}
};

#endif
