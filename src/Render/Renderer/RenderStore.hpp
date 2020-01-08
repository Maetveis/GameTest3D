#ifndef RENDER_RENDER_STORE_HPP
#define RENDER_RENDER_STORE_HPP

#include "FrameParams.hpp"
#include "LightParams.hpp"

#include <Render/Material/Material.hpp>
#include <Render/Model/RigidModel.hpp>
#include <Render/Model/ProtoModel.hpp>
#include <Render/Buffer/LinearBuffer.hpp>
#include <Render/ProgramInterface/ProgramInterface.hpp>
#include <Render/Scene/Scene.hpp>

#include <vector>

#include <GL/glew.h>

namespace Render
{

class RenderStore
{
private:
	std::vector<Material> materials;
	std::vector<RigidModel> models;
	std::vector<ProgramInterface> programs;

	LinearBuffer vertexBuffer;
	LinearBuffer indexBuffer;

	LinearBuffer materialBuffer;

	FrameParams frameParams;
public:
	RenderStore(GLuint vertexSize, GLuint indexSize) :
		vertexBuffer(vertexSize, GL_STATIC_DRAW),
		indexBuffer(indexSize, GL_STATIC_DRAW),
		materialBuffer(indexSize / 2, GL_STATIC_DRAW)
	{
	}

	unsigned AddMaterial(Material material)
	{
		materials.emplace_back(std::move(material));

		return materials.size() - 1;
	}

	Material& GetMaterial(unsigned id)
	{
		return materials[id];
	}

	unsigned AddModel(RigidModel model)
	{
		models.emplace_back(std::move(model));

		return models.size() - 1;
	}

	RigidModel& GetModel(unsigned id)
	{
		return models[id];
	}

	unsigned UploadModel(const ProtoModel& proto)
	{
		RigidModel model(0);

		for(auto& mesh : proto.meshes)
		{
			GLuint vertexOffset = PushVertex(mesh.vertices) / sizeof(mesh.vertices[0]);
			GLuint indexOffset  = std::visit([this](auto& vector){return this->PushIndex(vector);}, mesh.indices);
			model.AddMesh(Mesh(VertexBatch(mesh.GetIndexSize(), indexOffset, mesh.GetIndexType(), vertexOffset, GL_TRIANGLES), mesh.materialId));
		}

		return AddModel(std::move(model));
	}

	template <typename T>
	GLuint PushVertex(const std::vector<T>& vector)
	{
		return vertexBuffer.Push(vector).value();
	}

	template <typename T>
	GLuint PushIndex(const std::vector<T>& vector)
	{
		return indexBuffer.Push(vector).value();
	}

	template <typename T>
	GLuint PushMaterial(const T& value)
	{
		return materialBuffer.Push(value).value();
	}

	unsigned AddProgram(ProgramInterface interface)
	{
		programs.emplace_back(std::move(interface)).AttachFrameLight(frameParams.GetBinding());

		return programs.size() - 1;
	}

	ProgramInterface& GetProgram(unsigned id)
	{
		return programs[id];
	}

	const GL::Buffer& GetIndexBuffer() const
	{
		return indexBuffer.GetBuffer();
	}

	const GL::Buffer& GetVertexBuffer() const
	{
		return vertexBuffer.GetBuffer();
	}

	const GL::Buffer& GetMaterialBuffer() const
	{
		return materialBuffer.GetBuffer();
	}

	void UpdateScene(Scene& scene)
	{
		frameParams.Upload(scene.GetView(), scene.GetProj());
	}
};

} //namespace Render


#endif //RENDER_RENDER_STORE_HPP
