#ifndef RENDER_ASSIMP_IMPORT_FILE_HPP
#define RENDER_ASSIMP_IMPORT_FILE_HPP

#include "ProtoModel.hpp"

#include <Library/Logger/Logger.hpp>

#include <glm/vec3.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

namespace
{
	std::vector<PosNormUVFormat> GetVertices(const aiMesh& mesh)
	{
		std::vector<PosNormUVFormat> vertices;
		vertices.reserve(mesh.mNumVertices);

		const glm::vec2 zero = glm::vec2(0,0);
		for(unsigned i = 0; i < mesh.mNumVertices; ++i)
		{
			glm::vec3 const* p = reinterpret_cast<glm::vec3*>(&mesh.mVertices[i]);
			glm::vec3 const* n = reinterpret_cast<glm::vec3*>(&mesh.mNormals[i]);
			glm::vec2 const* uv = mesh.HasTextureCoords(i) ? reinterpret_cast<glm::vec2 const*>(&mesh.mTextureCoords[i]) : &zero;
			vertices.emplace_back(*p, *n, *uv);
		}

		return vertices;
	}

	template <typename T>
	std::vector<T> GetIndices(const aiMesh& mesh)
	{
		std::vector<T> indices;
		indices.reserve(mesh.mNumFaces * 3);

		for(unsigned face = 0; face < mesh.mNumFaces; ++face)
		{
			indices.emplace_back(mesh.mFaces[face].mIndices[0]);
			indices.emplace_back(mesh.mFaces[face].mIndices[1]);
			indices.emplace_back(mesh.mFaces[face].mIndices[2]);
		}
		return indices;
	}
}

namespace Render
{

ProtoModel AssimpImportFile(const std::string& filename)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(
		filename.c_str(),
			aiProcess_Triangulate |
			aiProcess_FlipUVs |
			aiProcess_GenSmoothNormals
	);

	if(!scene)
	{
		Logger::Warning() << "Error parsing file: " << filename << "\nAssimp error: " << importer.GetErrorString() << '\n';
		return ProtoModel();
	}

	ProtoModel model;

	for(unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		auto vertices = GetVertices(*scene->mMeshes[i]);

		ProtoMesh::IndexVector indices;
		if(scene->mMeshes[i]->mNumVertices < std::numeric_limits<GLubyte>::max())
			indices = GetIndices<GLubyte>(*scene->mMeshes[i]);
		else if (scene->mMeshes[i]->mNumVertices < std::numeric_limits<GLushort>::max())
			indices = GetIndices<GLushort>(*scene->mMeshes[i]);
		else
			indices = GetIndices<GLuint>(*scene->mMeshes[i]);

		model.meshes.push_back(ProtoMesh(std::move(vertices), std::move(indices), 0));
	}

	Logger::Debug() << "Successfully loaded " << filename << '\n';

	return model;
}

} //namespace Render

#endif	//RENDER_ASSIMP_IMPORT_FILE_HPP
