#include "ModelManager.h"

#include "../Log/Logger.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h> 

#include <algorithm>
#include <utility>

bool ModelManager::ImportFile(const std::string& filename, const std::string& meshname)
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
	
	Logger::Debug << "Assimp finished Loading" << '\n';
	
	std::vector<VertexFormat>          v;
	std::vector<Mesh3D::indexType>     indices;
	std::vector<int>                   gIC;
	std::vector<int>                   gVO;
	std::vector<Mesh3D::indexType*>    gIO;

	for(unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		gVO.emplace_back(v.size());
		gIO.emplace_back(static_cast<Mesh3D::indexType*>(0) + indices.size());
		
		gIC.emplace_back(InsertIndices(indices, scene->mMeshes[i]));
		InsertVertices(v, scene->mMeshes[i]);
	}
	
	Mesh3D& it = meshes[meshname];
	it.Init();
	it.MoveData(std::move(v), std::move(indices), std::move(gIC), std::move(gVO), std::move(gIO));
	it.BufferData();
	it.ClearLocalBuffer();
	
	Logger::Debug << "Finished converting" << '\n';
	
	return true;
}

void ModelManager::InsertVertices(std::vector<VertexFormat>& vertices, const aiMesh* mesh)
{
	const glm::vec3 zero = glm::vec3(0.,0.,0.);
	for (unsigned int i = 0 ; i < mesh->mNumVertices; ++i) {	
		const glm::vec3* p = reinterpret_cast<glm::vec3*>(mesh->mVertices + i);
		const glm::vec3* n = mesh->HasNormals() ? reinterpret_cast<glm::vec3*>(mesh->mNormals + i) : &zero;
        const glm::vec3* t = mesh->HasTextureCoords(0) ? reinterpret_cast<glm::vec3*>(mesh->mTextureCoords[0] + i) : &zero;
		
        vertices.emplace_back(*p, *n, *t);
    }
}

unsigned int ModelManager::InsertIndices(std::vector<Mesh3D::indexType>& indices, const aiMesh* mesh)
{
	for (unsigned int i = 0 ; i < mesh->mNumFaces; ++i) {
        const aiFace& Face = mesh->mFaces[i];
        indices.emplace_back(Face.mIndices[0]);
		indices.emplace_back(Face.mIndices[1]);
        indices.emplace_back(Face.mIndices[2]);
    }
	
	return mesh->mNumFaces * 3;
}

Mesh3D& ModelManager::Get(const std::string& name)
{
	return meshes.find(name)->second;
}

Mesh3D& ModelManager::operator[](const std::string& name)
{
	return meshes.find(name)->second;
}

const Mesh3D& ModelManager::Get(const std::string& name) const
{
	return meshes.find(name)->second;
}

const Mesh3D& ModelManager::operator[](const std::string& name) const
{
	return meshes.find(name)->second;
}