#ifndef RENDER_PROTO_MODEL_HPP
#define RENDER_PROTO_MODEL_HPP

#include <Render/VertexFormat/PosNormUVFormat.hpp>

#include <Library/IO/BinaryFileReader.hpp>
#include <Library/IO/BinaryFileWriter.hpp>

#include <Library/GL/TypeEnum.hpp>

#include <GL/glew.h>

#include <iostream>
#include <vector>
#include <variant>
#include <cstdint>

namespace Render
{

class ProtoMesh
{
public:
	using IndexVector =
		std::variant
		<
			std::vector<GLubyte>,
			std::vector<GLushort>,
			std::vector<GLuint>
		>;

	std::vector<PosNormUVFormat> vertices;
	IndexVector indices;
	size_t materialId;


	ProtoMesh(std::vector<PosNormUVFormat>&& _vertices, IndexVector&& _indices, size_t _materialId = 0) :
		vertices(_vertices),
		indices(_indices),
		materialId(_materialId)
	{
	}

	ProtoMesh() = default;

	size_t GetIndexSize() const
	{
		return std::visit([](auto& vector){return vector.size();}, indices);
	}

	GLenum GetIndexType() const
	{
		return std::visit([](auto& vector){return GL::GetTypeEnum(vector[0]);}, indices);
	}

	friend IO::BinaryFileReader& operator>>(IO::BinaryFileReader& lhs, ProtoMesh& rhs);
	friend IO::BinaryFileWriter& operator<<(IO::BinaryFileWriter& lhs, const ProtoMesh& rhs);
};

inline IO::BinaryFileReader& operator>>(IO::BinaryFileReader& lhs, ProtoMesh& rhs)
{
	size_t vertexCount;
	lhs.ReadBitWise(&vertexCount);
	rhs.vertices.resize(vertexCount);
	lhs.ReadBuffer(rhs.vertices.data(), vertexCount);

	size_t indexCount;
	lhs.ReadBitWise(&indexCount);
	if(vertexCount < std::numeric_limits<GLubyte>::max())
		rhs.indices.emplace< std::vector<GLubyte> >();
	else if (vertexCount < std::numeric_limits<GLushort>::max())
		rhs.indices.emplace< std::vector<GLushort> >();
	else
		rhs.indices.emplace< std::vector<GLuint> >();

	std::visit([indexCount](auto& vector){vector.resize(indexCount);}, rhs.indices);
	std::visit([&lhs, indexCount](auto& vector){lhs.ReadBuffer(vector.data(), indexCount);}, rhs.indices);

	lhs.ReadBitWise(&rhs.materialId);

	return lhs;
}

inline IO::BinaryFileWriter& operator<<(IO::BinaryFileWriter& lhs, const ProtoMesh& rhs)
{
	size_t vertexCount = rhs.vertices.size();
	lhs.WriteBitWise(vertexCount);
	lhs.WriteBuffer(rhs.vertices.data(), rhs.vertices.size());

	size_t indexCount = std::visit([](const auto& vector){return vector.size();}, rhs.indices);
	lhs.WriteBitWise(indexCount);
	std::visit([&lhs](auto& vector){lhs.WriteBuffer(vector.data(), vector.size());}, rhs.indices);

	lhs.WriteBitWise(rhs.materialId);

	return lhs;
}

class ProtoModel
{
public:
	std::vector<ProtoMesh> meshes;
	ProtoModel() = default;

	ProtoModel(const ProtoModel&){std::cout << "copy\n";};

	ProtoModel(ProtoModel&&){std::cout << "move\n";};

	friend IO::BinaryFileReader& operator>>(IO::BinaryFileReader& lhs, ProtoModel& rhs);
	friend IO::BinaryFileWriter& operator<<(IO::BinaryFileWriter& lhs, const ProtoModel& rhs);
};

inline IO::BinaryFileReader& operator>>(IO::BinaryFileReader& lhs, ProtoModel& rhs)
{
	if(lhs.GetHeader().magic != 0x35334D4553348533 || lhs.GetHeader().major != 0 || lhs.GetHeader().minor != 1)
		return lhs;

	uint64_t meshCount;
	lhs.ReadBitWise(&meshCount);
	rhs.meshes.resize(meshCount);

	for(auto& mesh : rhs.meshes)
	{
		lhs >> mesh;
	}

	return lhs;
};

inline IO::BinaryFileWriter& operator<<(IO::BinaryFileWriter& lhs, const ProtoModel& rhs)
{
	lhs.WriteHeader(IO::FileHeader{0x35334D4553348533, 0, 1});
	uint64_t meshCount = rhs.meshes.size();

	lhs.WriteBitWise(meshCount);

	for(const auto& mesh : rhs.meshes)
	{
		lhs << mesh;
	}

	return lhs;
}

} //namespace Render

#endif //RENDER_PROTO_MODEL_HPP
