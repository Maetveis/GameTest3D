#ifndef RENDER_VERTEX_BATCH_HPP
#define RENDER_VERTEX_BATCH_HPP

#include <GL/glew.h>

namespace Render
{

class VertexBatch
{
private:
	// number of indices
	GLuint indexCount;

	// starting position (in bytes) of indices in buffer
	GLuint indexOffset;

	// byte or short or unisgned (depending on number of indices)
	GLenum indexType;

	/*
		starting position of vertices in buffer (number of vertexes before)
		will be added to each index
	*/
	GLuint baseVertex;

	// primitive type for drawing (Triangle, Line, Strip etc)
	GLenum renderMode;
public:

	VertexBatch
	(
		GLuint _indexCount,
		GLuint _indexOffset,
		GLuint _indexType,
		GLuint _baseVertex,
		GLuint _renderMode
	) :
		indexCount(_indexCount),
		indexOffset(_indexOffset),
		indexType(_indexType),
		baseVertex(_baseVertex),
		renderMode(_renderMode)
	{
	}

	/*
		Send the data to the draw call, assuming buffer is already bound
	*/
	void Draw() const
	{
		glDrawElementsBaseVertex
		(
			renderMode,
			indexCount,
			indexType,
			static_cast<char *>(0) + indexOffset, //this requires a pointer
			baseVertex
		);
	}

};

} //namespace Render

#endif //RENDER_VERTEX_BATCH_HPP
