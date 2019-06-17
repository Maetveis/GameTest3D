#include "Scene.hpp"

#include "../Model/ModelLoader.hpp"
#include "../VertexFormat/PosNormUVDescriptor.hpp"

#include <GL/glew.h>

#include <utility>

namespace Render
{

Scene::Scene():
	vertexBuffer(5000000, GL_STATIC_DRAW),
	indexBuffer(5000000, GL_STATIC_DRAW)
{
}

void Scene::AddObject(const std::string& name, const glm::mat4& transform)
{
	auto it = models.find(name);
	if(it != models.end())
	{
		objects.emplace_back(*it->second.get(), transform);
	}
	else
	{
		ModelLoader loader(vertexBuffer, indexBuffer, materials);
		decltype(models.begin()) it;
		std::tie(it, std::ignore) = models.insert(std::make_pair(name, std::make_unique<RigidModel>()));
		RigidModel& model = *it->second.get();
		loader.ImportFile(name, model);
		objects.emplace_back(model, transform);
	}
}

void Scene::BindIndexVertexBuffer(PosNormUVDescriptor& va) const
{
	va.BindVertexBuffer(vertexBuffer);
	va.BindIndexBuffer(indexBuffer);
}

} //namespace Render
