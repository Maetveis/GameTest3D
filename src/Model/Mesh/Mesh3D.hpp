#ifndef MESH3D_H
#define MESH3D_H

#include "../../Library/GL/Range.hpp"

#include <GL/glew.h>

class Mesh3D
{
private:
	GL::Range vertexRange;
	GL::Range indexRange;

	GLuint indexCount;

	GLenum type;

public:
	Mesh3D(GL::Range _vertexRange, GL::Range _indexRange, GLuint _indexCount ,GLenum _type = GL_UNSIGNED_SHORT);

	Mesh3D(const Mesh3D&) = delete;
	Mesh3D(Mesh3D&&) = default;

	Mesh3D& operator=(const Mesh3D&) = delete;

	Mesh3D& operator=(Mesh3D&&) = default;

	void Draw() const;

	GL::Range GetVertexRange() const;
	GL::Range GetIndexRange() const;
	GLuint GetIndexCount() const;
};

#endif //MESH3D_H
