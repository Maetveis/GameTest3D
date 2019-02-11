#include "ModelManager.h"

#include "../Log/Logger.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <algorithm>

ModelManager::ModelManager()
{
	glVertexArrayElementBuffer(desc.Get(), indexBuffer.GetId());
	desc.Attach(vertexBuffer);

	vertexBuffer.BufferData(100000000, nullptr, GL_STATIC_DRAW);
	indexBuffer.BufferData(100000000, nullptr, GL_STATIC_DRAW);
}

void ModelManager::Draw(const std::string& name) const
{
	auto it = models.find(name);
	const RigidModel& model = it->second;

	desc.Bind();
	for(unsigned i = 0; i < model.meshes.size(); ++i)
	{
		model.meshes[i].Draw();
	}
}

bool ModelManager::ImportFile(const std::string& filename, const std::string& name)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(
		filename.c_str(),
			aiProcess_Triangulate |
			aiProcess_FlipUVs |
			aiProcess_GenNormals |
			aiProcess_JoinIdenticalVertices
	);

	if(!scene)
	{
		Logger::Warning << "Error parsing file: " << filename << "\nAssimp error: " << importer.GetErrorString() << '\n';
		return false;
	}

	RigidModel newModel;
	for(unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		auto vertex = InsertVertices(*scene->mMeshes[i]);
		auto index = InsertIndices(*scene->mMeshes[i]);

		//if(scene->mMeshes[i]->mNumVertices > 10000)
			newModel.meshes.emplace_back(vertex.first, (GLint) vertex.second, (char*)(0) + index.first, index.second, GL_UNSIGNED_INT);
		//else
		//	newModel.meshes.emplace(vertexOffset, vertexSize, indexPointer, indexCount, GL_UNSIGNED_SHORT);
	}

	models[name] = std::move(newModel);

	Logger::Debug << "Successfully loaded " << filename << '\n';

	return true;
}

std::pair<GLuint, GLuint> ModelManager::InsertIndices (const aiMesh& mesh)
{
	std::vector<GLuint> indices;
	indices.reserve(mesh.mNumFaces * 3);

	for(unsigned face = 0; face < mesh.mNumFaces; ++face)
	{
		indices.emplace_back(mesh.mFaces[face].mIndices[0]);
		indices.emplace_back(mesh.mFaces[face].mIndices[1]);
		indices.emplace_back(mesh.mFaces[face].mIndices[2]);
	}

	GLuint indexCount = indices.size();
	GLuint offset;
	if(!indexAllocator.Allocate(indexCount * sizeof(GLuint), sizeof(GLuint), &offset))
		Logger::Error << "Index Allocation failed" << '\n';

	indexBuffer.BufferSubData(offset, indices, GL_STATIC_DRAW);
	return std::make_pair(offset, indexCount);
}

std::pair<GLuint, GLuint> ModelManager::InsertVertices(const aiMesh& mesh)
{
	std::vector<BasicVertexFormat> vertices;
	vertices.reserve(mesh.mNumVertices);

	auto zero = glm::vec2(0,0);
	for(unsigned i = 0; i < mesh.mNumVertices; ++i)
	{
		glm::vec3 const* p = reinterpret_cast<glm::vec3*>(&mesh.mVertices[i]);
		glm::vec3 const* n = reinterpret_cast<glm::vec3*>(&mesh.mNormals[i]);
		glm::vec2 const* uv = mesh.HasTextureCoords(i) ? reinterpret_cast<glm::vec2 const*>(&mesh.mTextureCoords[i]) : &zero;
		vertices.emplace_back(*p, *n, *uv);
	}

	GLuint offset;
	GLuint vertexSize = static_cast<GLuint> (vertices.size() * sizeof(BasicVertexFormat));
	if(!vertexAllocator.Allocate(vertexSize, sizeof(BasicVertexFormat), &offset))
		Logger::Error << "Vertex Allocation failed" << '\n';

	vertexBuffer.BufferSubData(offset, vertices, GL_STATIC_DRAW);

	return std::make_pair(offset / sizeof(BasicVertexFormat), vertexSize);
}

/*Mesh3D& ModelManager::Get(const std::string& name)
{
	return models.find(name)->second;
}

Mesh3D& ModelManager::operator[](const std::string& name)
{
	return models.find(name)->second;
}*/

const RigidModel& ModelManager::Get(const std::string& name) const
{
	return models.find(name)->second;
}

const RigidModel& ModelManager::operator[](const std::string& name) const
{
	return models.find(name)->second;
}
