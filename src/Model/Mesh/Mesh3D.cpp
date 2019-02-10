#include "Mesh3D.h"

#include "../../Log/Logger.h"

#include <algorithm>
#include <numeric>

Mesh3D::Mesh3D(
	std::vector<BasicVertexFormat>&&  v,
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
	std::vector<BasicVertexFormat>&&  v,
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
	/*
	// Generate 1 VAO
	glGenVertexArrays(1, &vertexId);
	glBindVertexArray(vertexId);

	//Generate buffers
	GLuint buffers[2];
	glGenBuffers(2, buffers);
	vertexBufferID = buffers[0];
	indexBufferID = buffers[1];

	glBindVertexArray(vertexId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

	//glVertexArrayElementBuffer(vertexId, indexBufferID);

	//BasicVertexFormat::SetGLAttributes(attributeID, vertexBufferID);

	//Set first attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BasicVertexFormat), 0);

	//Set Second attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BasicVertexFormat), (void*)sizeof(BasicVertexFormat::pos));

	//Set Third attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BasicVertexFormat), (void*)offsetof(BasicVertexFormat, uv));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//
	idáig*/

	//vertexBuffer.Bind(GL_ARRAY_BUFFER);
	//indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);

	glVertexArrayElementBuffer(desc.Get(), indexBuffer.GetId());
	desc.Attach(vertexBuffer);

	groupCount = 0;
}

void Mesh3D::BufferData()
{
	/*
	//vertexBuffer.BufferData(vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(BasicVertexFormat), (void*)vertices.data(), GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), (void*)indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glNamedBufferData(vertexBufferID, vertices.size() * sizeof(BasicVertexFormat), (void*)vertices.data(), GL_STATIC_DRAW);
	glNamedBufferData(indexBufferID, indices.size() * sizeof(indices[0]), (void*)indices.data(), GL_STATIC_DRAW);
	//indexBuffer.BufferData(indices, GL_STATIC_DRAW);
	idáig
	*/

	vertexBuffer.BufferData(vertices, GL_STATIC_DRAW);
	indexBuffer.BufferData(indices, GL_STATIC_DRAW);

	groupCount = groupIndexCount.size();

	Logger::Debug << "#vertices: " << vertices.size() << '\n';
	Logger::Debug << "#indices: " << indices.size() << '\n';
	Logger::Debug << "groupCount: " << groupCount << '\n';

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Mesh3D::ClearLocalBuffer()
{
	vertices.clear();
	indices.clear();
}

void Mesh3D::DrawAll()
{
	/*desc.Bind();
	glBindVertexArray(vertexId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	//indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);*/

	desc.Bind();
	//indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);
	//vertexBuffer.Bind(GL_ARRAY_BUFFER);

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
	//desc.Bind();
	//glBindVertexArray(vertexId);
	//indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);

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
