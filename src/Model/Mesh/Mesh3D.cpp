#include "Mesh3D.hpp"

#include "BasicVertexFormat.h"

Mesh3D::Mesh3D(GL::Range _vertexRange, GL::Range _indexRange, GLuint _indexCount ,GLenum _type) :
	vertexRange(_vertexRange),
	indexRange(_indexRange),
	indexCount(_indexCount),
	type(_type)
{
}

void Mesh3D::Draw() const
{
	glDrawElementsBaseVertex
	(
		GL_TRIANGLES,
		indexCount,
		type,
		static_cast<char *>(0) + indexRange.offset,
		vertexRange.offset / sizeof(BasicVertexFormat)
	);
}

GL::Range Mesh3D::GetVertexRange() const
{
	return vertexRange;
}

GL::Range Mesh3D::GetIndexRange() const
{
	return indexRange;
}

GLuint Mesh3D::GetIndexCount() const
{
	return indexCount;
}
