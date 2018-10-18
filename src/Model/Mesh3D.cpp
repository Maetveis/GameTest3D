#include "Mesh3D.h"

#include "../Log/Logger.h"

#include <algorithm>
#include <numeric>

Mesh3D::Mesh3D( 
	std::vector<VertexFormat>&&  v,
	std::vector<indexType>&&     i,
	std::vector<int>&&           gIC,
	std::vector<int>&&           gVO,
	std::vector<indexType*>&&    gIO
) : 
	vertices(v),
	indices(i),
	groupIndexCount(gIC),
	groupVertexOffset(gVO),
	groupIndexOffset(gIO)
{
}

void Mesh3D::MoveData( 
	std::vector<VertexFormat>&&  v,
	std::vector<indexType>&&     i,
	std::vector<int>&&           gIC,
	std::vector<int>&&           gVO,
	std::vector<indexType*>&&    gIO
)
{
	vertices = v;
	indices = i;
	groupIndexCount = gIC;
	groupVertexOffset = gVO;
	groupIndexOffset = gIO;
}

void Mesh3D::Init()
{
	// Generate 1 VAO
	glGenVertexArrays(1, &attributeID);
	glBindVertexArray(attributeID);
	
	//Generate buffers
	GLuint buffers[2];
	glGenBuffers(2, buffers);
	vertexBufferID = buffers[0];
	indexBufferID = buffers[1];
	
	VertexFormat::SetGLAttributes(attributeID, vertexBufferID);
	
	groupCount = 0;
}

void Mesh3D::BufferData()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER,  vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indexType), &indices[0], GL_STATIC_DRAW);
	
	groupCount = groupIndexCount.size();
}

void Mesh3D::ClearLocalBuffer()
{
	vertices.clear();
	indices.clear();
}

void Mesh3D::DrawAll()
{
	glBindVertexArray(attributeID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
 	
	//Has to be changed if indexType changes
	glMultiDrawElementsBaseVertex
	(
		GL_TRIANGLES,
		groupIndexCount.data(),
		GL_UNSIGNED_SHORT,
		reinterpret_cast<void**>(groupIndexOffset.data()),
		groupCount,
		groupVertexOffset.data()
	);
	
	glBindVertexArray(0);
}

void Mesh3D::DrawSubMesh(std::size_t index)
{
	glBindVertexArray(attributeID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
 	
	//Has to be changed if indexType changes
	glDrawElementsBaseVertex
	(
		GL_TRIANGLES,
		groupIndexCount[index],
		GL_UNSIGNED_SHORT,
		reinterpret_cast<void*>(groupIndexOffset[index]),
		groupVertexOffset[index]
	);
	
	glBindVertexArray(0);
}
