#ifndef RENDER_OBJECT_RENDERER_HPP
#define RENDER_OBJECT_RENDERER_HPP

#include "RenderStore.hpp"

#include <Render/VertexFormat/PosNormUVDescriptor.hpp>
#include <Render/Resource/ResourceManager.hpp>
#include <Render/Material/Material.hpp>
#include <Render/Model/RigidModel.hpp>

#include <Library/GL/Program.hpp>
#include <Library/GL/Buffer.hpp>

#include <vector>

namespace Render
{
	class Scene;
}

namespace Render
{

class ObjectRenderer
{
private:
	Scene& scene;
	RenderStore& store;

	PosNormUVDescriptor descriptor;
public:
	ObjectRenderer(Scene& _scene, RenderStore& _store);

	void ResizeViewPort(int newWidth, int newHeight);
	void Render();
};

} //namespace Render

#endif //RENDER_OBJECT_RENDERER_HPP
