#ifndef RENDER_MESH_HPP
#define RENDER_MESH_HPP

#include "../../Library/GL/Range.hpp"

#include <GL/glew.h>

namespace Render
{

class Mesh
{
private:
	GL::Range vertexRange;
	GL::Range indexRange;

	GLuint vertexOffset;
	GLuint indexCount;

	GLenum type;

public:
	Mesh(
		GL::Range _vertexRange,
		GL::Range _indexRange,
		GLuint _vertexOffset,
		GLuint _indexCount,
		GLenum _type
	);

	Mesh(const Mesh&) = delete;
	Mesh(Mesh&&) = default;

	Mesh& operator=(const Mesh&) = delete;

	Mesh& operator=(Mesh&&) = default;

	void Draw() const;

	GL::Range GetVertexRange() const;
	GL::Range GetIndexRange() const;
	GLuint GetIndexCount() const;
};

}

#endif //RENDER_MESH_HPP
