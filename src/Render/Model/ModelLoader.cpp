#include "ModelLoader.hpp"

#include "RigidModel.hpp"
#include "Mesh.hpp"
#include "VertexBatch.hpp"

#include <Render/Material/ColorFormat.hpp>
#include <Render/Material/Material.hpp>
#include <Render/Renderer/RenderStore.hpp>

#include <Render/VertexFormat/PosNormUVFormat.hpp>

#include <Library/GL/TypeEnum.hpp>
#include <Library/Logger/Logger.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <limits>

namespace Render
{

bool ModelLoader::ImportFile(const std::string& filename, RigidModel& newModel)
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
		Logger::Warning() << "Error parsing file: " << filename << "\nAssimp error: " << importer.GetErrorString() << '\n';
		return false;
	}

	for(unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		GLuint vertexOffset = InsertVertices(GetVertices(*scene->mMeshes[i]));

//		newModel.materials.emplace_back(materialParams.AddRandomMaterial());

		if(scene->mMeshes[i]->mNumVertices < std::numeric_limits<GLubyte>::max())
			HandleIndices<GLubyte>(*scene->mMeshes[i], newModel, vertexOffset);
		else if (scene->mMeshes[i]->mNumVertices < std::numeric_limits<GLushort>::max())
			HandleIndices<GLushort>(*scene->mMeshes[i], newModel, vertexOffset);
		else
			HandleIndices<GLuint>(*scene->mMeshes[i], newModel, vertexOffset);
	}

	Logger::Debug() << "Successfully loaded " << filename << '\n';

	return true;
}

template <typename T>
void ModelLoader::HandleIndices(const aiMesh& mesh, RigidModel& model, GLuint vertexOffset)
{
	std::vector<T> vec = GetIndices<T>(mesh);
	GLuint indexOffset = InsertIndices(vec);
	model.AddMesh(Mesh(VertexBatch(vec.size(), indexOffset, GL::TypeEnum<T>::value, vertexOffset, GL_TRIANGLES), 0));
}

template <typename T>
GLuint ModelLoader::InsertIndices (const std::vector<T>& vector)
{
	return store.PushIndex(vector);
}

GLuint ModelLoader::InsertVertices(const std::vector<PosNormUVFormat>& vertices)
{
	return store.PushVertex(vertices) / sizeof(vertices.front());
}

template <typename T>
std::vector<T> ModelLoader::GetIndices(const aiMesh& mesh)
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

std::vector<PosNormUVFormat> ModelLoader::GetVertices(const aiMesh& mesh)
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

} //namespace Render
