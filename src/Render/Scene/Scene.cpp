#include "Scene.hpp"

#include <Render/Model/ModelLoader.hpp>
#include <Render/VertexFormat/PosNormUVDescriptor.hpp>

#include <GL/glew.h>

#include <utility>

namespace Render
{

Scene::Scene()
{
}

void Scene::AddObject(Object object)
{
	objects.emplace_back(std::move(object));
}

} //namespace Render
