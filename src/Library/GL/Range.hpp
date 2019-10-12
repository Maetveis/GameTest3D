#ifndef GL_RANGE
#define GL_RANGE

#include <GL/glew.h>

namespace GL
{

class Range
{
public:
	GLuint offset;
	GLuint size;

	Range(GLuint _offset, GLuint _size = 0) :
		offset(_offset),
		size(_size)
	{
	}

	Range(const Range&)  = default;

	bool operator==(const Range& rhs)
	{
		return offset == rhs.offset && size == rhs.size;
	}

	bool operator!=(const Range& rhs)
	{
		return offset != rhs.offset || size != rhs.size;
	}
};

} //namespace GL

#endif //GL_RANGE
