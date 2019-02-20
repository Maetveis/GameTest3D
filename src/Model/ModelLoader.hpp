#ifndef MODEL_LOADER_HPP
#define MODEL_LOADER_HPP

#include "../DataStore/ManagedBuffer.hpp"
#include "Mesh/BasicVertexFormat.h"
#include "RigidModel.hpp"

#include <vector>
#include <string>
#include <type_traits>

template <typename T>
struct always_false
{
	static constexpr bool value = false;
};

template <typename T>
struct GLIndexType
{
	static_assert(always_false<T>::value, "Undefined");
	static constexpr GLenum value = 0;
};

template <>
struct GLIndexType<GLuint>
{
	static constexpr GLenum value = GL_UNSIGNED_INT;
};

template <>
struct GLIndexType<GLushort>
{
	static constexpr GLenum value = GL_UNSIGNED_SHORT;
};

template <>
struct GLIndexType<GLubyte>
{
	static constexpr GLenum value = GL_UNSIGNED_BYTE;
};

class aiMesh;
class Mesh3D;
class MaterialParams;

class ModelLoader
{
private:
	ManagedBuffer& vertexBuffer;
	ManagedBuffer& indexBuffer;
	MaterialParams& materialParams;

	template <typename T>
	void HandleIndices(const aiMesh& mesh, RigidModel& model, const std::pair<GLuint, GLuint>& vertex)
	{
		std::vector<T> vec = GetIndices<T>(mesh);
		GLuint indexOffset = InsertIndices(vec.size() * sizeof(T), vec.data(), sizeof(T));
		model.meshes.emplace_back(vertex.first, (GLint) vertex.second, (char*)(0) + indexOffset, vec.size(), GLIndexType<T>::value);
	}

	std::pair<GLuint, GLuint> InsertVertices(const std::vector<BasicVertexFormat>& vertices);
	GLuint InsertIndices (GLuint size, const void* data, GLuint alignment);

	template <typename T>
	std::vector<T> GetIndices(const aiMesh& mesh);

	template <typename T>
	void PushIndex(Mesh3D& mesh, RigidModel& model);

	std::vector<BasicVertexFormat> GetVertices(const aiMesh& mesh);
public:
	ModelLoader(ManagedBuffer& _vertexBuffer, ManagedBuffer& _indexBuffer, MaterialParams& _materialParams) :
		vertexBuffer(_vertexBuffer),
		indexBuffer(_indexBuffer),
		materialParams(_materialParams)
	{
		srand(time(0));
	}

	RigidModel ImportFile(const std::string& filename);
};

#endif
