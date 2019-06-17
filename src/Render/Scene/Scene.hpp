#ifndef RENDER_SCENE_HPP
#define RENDER_SCENE_HPP

#include "FrameParams.hpp"
#include "LightParams.hpp"
#include "Object.hpp"

#include "../Model/RigidModel.hpp"
#include "../Material/MaterialParams.hpp"

#include "../../DataStore/ManagedBuffer.hpp"

#include <glm/mat4x4.hpp>

#include <vector>
#include <map>
#include <memory>

namespace GL
{
	class Program;
}

namespace Render
{
	class Light;
	class PosNormUVDescriptor;
}

namespace Render
{

class Scene
{
private:
	LightParams lights;
	FrameParams frameParams;
	MaterialParams materials;

	std::vector<Object> objects;
	std::map<std::string, std::unique_ptr<RigidModel> > models;

	ManagedBuffer vertexBuffer;
	ManagedBuffer indexBuffer;
public:
	Scene();

	void AddLight(const Light& light)
	{
		lights.AddLight(light);
	}

	void SetProj(const glm::mat4& proj)
	{
		frameParams.SetProj(proj);
	}

	void SetView(const glm::mat4& view)
	{
		frameParams.SetView(view);
	}

	void BindParams(const GL::Program& program)
	{
		lights.Bind(program);
		frameParams.Bind(program);
		materials.Bind(program);
	}

	void UseMaterial(size_t id)
	{
		materials.UseMaterial(id);
	}


	void BindIndexVertexBuffer(PosNormUVDescriptor& va) const;

	void AddObject(const std::string& name, const glm::mat4& transform);

	const std::vector<Object>& GetObjects() const
	{
		return objects;
	}

	void Update()
	{
		 lights.Update();
		 frameParams.Update();
	}
};

} //namespace Render

#endif //RENDER_SCENE_HPP
