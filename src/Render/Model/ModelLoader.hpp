#ifndef RENDER_MODEL_LOADER_HPP
#define RENDER_MODEL_LOADER_HPP

#include <Render/VertexFormat/PosNormUVFormat.hpp>

#include <vector>
#include <string>
#include <type_traits>
#include <cstdlib>
#include <ctime>

#include <GL/glew.h>

class aiMesh;
class ManagedBuffer;

namespace Render
{
	class RigidModel;
	class Mesh;
	class MaterialParams;
	class RenderStore;
}

namespace Render
{

class ModelLoader
{
private:
	RenderStore& store;

	template <typename T>
	void HandleIndices(const aiMesh& mesh, RigidModel& model, GLuint vertexOffset);

	GLuint InsertVertices(const std::vector<PosNormUVFormat>& vertices);

	template <typename T>
	GLuint InsertIndices (const std::vector<T>& vector);

	template <typename T>
	std::vector<T> GetIndices(const aiMesh& mesh);

	template <typename T>
	void PushIndex(Mesh& mesh, RigidModel& model);

	std::vector<PosNormUVFormat> GetVertices(const aiMesh& mesh);
public:
	ModelLoader(RenderStore& _store) :
		store(_store)
	{
		srand(time(0));
	}

	bool ImportFile(const std::string& filename, RigidModel& model);
};

} //namespace Render

#endif //RENDER_MODEL_LOADER_HPP
