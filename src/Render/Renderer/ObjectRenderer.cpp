#include "ObjectRenderer.hpp"

#include "../Scene/Scene.hpp"

#include "../../Library/Logger/Logger.hpp"

#include <GL/glew.h>

namespace
{
	constexpr const char* VertFileName = "../shaders/blinPhongVert.glsl";
	constexpr const char* FragFileName = "../shaders/blinPhongFrag.glsl";
}

namespace Render
{

ObjectRenderer::ObjectRenderer(Scene& _scene):
	scene(_scene)
{
	glClearColor(0.3, 0., 0., 1.);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);


	renderProgram.VsFsProgram(VertFileName, FragFileName);
	scene.BindParams(renderProgram);
	scene.BindIndexVertexBuffer(descriptor);
}

void ObjectRenderer::ResizeViewPort(int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
}


void ObjectRenderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	descriptor.Bind();
	renderProgram.Use();

	GLuint modelId = renderProgram.GetUniformLocation("model");

	for(const Object& object: scene.GetObjects())
	{
		for(size_t i = 0; i < object.model.meshes.size(); ++i)
		{
			glUniformMatrix4fv(modelId, 1, false, &(object.transform[0][0]));
			scene.UseMaterial(object.model.materials[i]);
			object.model.meshes[i].Draw();
		}
	}
}

} //namespace Render
