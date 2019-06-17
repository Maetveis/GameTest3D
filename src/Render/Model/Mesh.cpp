#include "Mesh.hpp"

namespace Render {

Mesh::Mesh(
	GL::Range _vertexRange,
	GL::Range _indexRange,
	GLuint _vertexOffset,
	GLuint _indexCount,
	GLenum _type
):
	vertexRange(_vertexRange),
	indexRange(_indexRange),
	vertexOffset(_vertexOffset),
	indexCount(_indexCount),
	type(_type)
{
}

void Mesh::Draw() const
{
	glDrawElementsBaseVertex
	(
		GL_TRIANGLES,
		indexCount,
		type,
		static_cast<char *>(0) + indexRange.offset,
		vertexOffset
	);
}

GL::Range Mesh::GetVertexRange() const
{
	return vertexRange;
}

GL::Range Mesh::GetIndexRange() const
{
	return indexRange;
}

GLuint Mesh::GetIndexCount() const
{
	return indexCount;
}

}
