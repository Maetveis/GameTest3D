#ifndef RENDER_MODEL_LOADER_HPP
#define RENDER_MODEL_LOADER_HPP

#include "../VertexFormat/PosNormUVFormat.hpp"

#include "../../Library/GL/TypeEnum.hpp"

#include <vector>
#include <string>
#include <type_traits>
#include <cstdlib>
#include <ctime>

class aiMesh;
class ManagedBuffer;

namespace GL
{
	class Range;
}

namespace Render
{
	class RigidModel;
	class Mesh;
	class MaterialParams;
}

namespace Render
{

class ModelLoader
{
private:
	ManagedBuffer& vertexBuffer;
	ManagedBuffer& indexBuffer;
	MaterialParams& materialParams;

	template <typename T>
	void HandleIndices(const aiMesh& mesh, RigidModel& model, GL::Range vertexRange);

	GL::Range InsertVertices(const std::vector<PosNormUVFormat>& vertices);
	GL::Range InsertIndices (GLuint size, const void* data, GLuint alignment);

	template <typename T>
	std::vector<T> GetIndices(const aiMesh& mesh);

	template <typename T>
	void PushIndex(Mesh& mesh, RigidModel& model);

	std::vector<PosNormUVFormat> GetVertices(const aiMesh& mesh);
public:
	ModelLoader(ManagedBuffer& _vertexBuffer, ManagedBuffer& _indexBuffer, MaterialParams& _materialParams) :
		vertexBuffer(_vertexBuffer),
		indexBuffer(_indexBuffer),
		materialParams(_materialParams)
	{
		srand(time(0));
	}

	bool ImportFile(const std::string& filename, RigidModel& model);
};

} //namespace Render

#endif //RENDER_MODEL_LOADER_HPP
