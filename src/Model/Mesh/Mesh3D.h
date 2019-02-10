#ifndef MESH3D_H
#define MESH3D_H

#include "BasicVertexFormat.h"
#include "BasicVertexDescriptor.hpp"

#include <vector>
#include <GL/glew.h>

class Mesh3D
{
public:
	using indexType = unsigned short;

	Mesh3D() = default;

	Mesh3D(
		std::vector<BasicVertexFormat>&& v,
		std::vector<indexType>&&    i,
		std::vector<int>&&          gIC,
		std::vector<int>&&          gVO,
		std::vector<indexType*>&&   gIO
	);

	void MoveData(
		std::vector<BasicVertexFormat>&& v,
		std::vector<indexType>&&    i,
		std::vector<int>&&          gIC,
		std::vector<int>&&          gVO,
		std::vector<indexType*>&&   gIO
	);

	std::size_t GetSubMeshCount() const
	{
		return groupCount;
	}

	void Init();
	void BufferData();
	void ClearLocalBuffer();
	void DrawAll();
	void DrawSubMesh(std::size_t index);
private:
	BasicVertexDescriptor desc;
	Buffer vertexBuffer;
	Buffer indexBuffer;

	/*GLuint vertexId;
	GLuint indexBufferID;
	GLuint vertexBufferID;*/


	unsigned int groupCount;

	std::vector<BasicVertexFormat> vertices;
	std::vector<indexType>    indices;
	std::vector<GLint>        groupIndexCount;
	std::vector<GLint>        groupVertexOffset;
	std::vector<indexType*>   groupIndexOffset;
};

#endif //MESH3D_H
