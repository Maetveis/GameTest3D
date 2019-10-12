#ifndef RENDER_SCENE_HPP
#define RENDER_SCENE_HPP

#include "Object.hpp"
#include "Light.hpp"

#include <Render/Model/RigidModel.hpp>
#include <Render/Material/Material.hpp>
#include <Render/Resource/ResourceManager.hpp>


#include <DataStore/ManagedBuffer.hpp>

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
	class PosNormUVDescriptor;
	class ProgramInterface;
}

namespace Render
{

class Scene
{
private:
	std::vector<Light> lights;

	glm::mat4 view;
	glm::mat4 proj;

	std::vector<Object> objects;
public:
	Scene();

	void AddLight(Light light)
	{
		lights.emplace_back(std::move(light));
	}

	void SetProj(const glm::mat4& _proj)
	{
		proj = _proj;
	}

	void SetView(const glm::mat4& _view)
	{
		view = _view;
	}

	void AddObject(Object object);

	const std::vector<Object>& GetObjects() const
	{
		return objects;
	}

	const glm::mat4& GetView() const
	{
		return view;
	}

	const glm::mat4& GetProj() const
	{
		return proj;
	}

	const std::vector<Light>& GetLights() const
	{
		return lights;
	}
};

} //namespace Render

#endif //RENDER_SCENE_HPP
