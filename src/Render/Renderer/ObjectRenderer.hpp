#ifndef RENDER_OBJECT_RENDERER_HPP
#define RENDER_OBJECT_RENDERER_HPP

#include "../VertexFormat/PosNormUVDescriptor.hpp"
#include "../Model/RigidModel.hpp"

#include "../../Library/GL/Program.hpp"
#include "../../Library/GL/Buffer.hpp"

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

	GL::Program renderProgram;
	PosNormUVDescriptor descriptor;

	std::vector<RigidModel> models;
public:
	ObjectRenderer(Scene& _scene);

	void ResizeViewPort(int newWidth, int newHeight);
	void Render();
};

} //namespace Render

#endif //RENDER_OBJECT_RENDERER_HPP
