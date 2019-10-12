#include "ObjectRenderer.hpp"

#include <Render/Scene/Scene.hpp>
#include <Render/Scene/Object.hpp>
#include <Render/ProgramInterface/ProgramInterface.hpp>

#include <Library/GL/SetUniform.hpp>

#include <Library/Logger/Logger.hpp>

#include <GL/glew.h>

#include <iostream>

namespace Render
{

ObjectRenderer::ObjectRenderer(Scene& _scene, RenderStore& _store) :
	scene(_scene),
	store(_store)
{
	glClearColor(0.3, 0., 0., 1.);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);

	descriptor.BindIndexBuffer(store.GetIndexBuffer());
	descriptor.BindVertexBuffer(store.GetVertexBuffer());
}

void ObjectRenderer::ResizeViewPort(int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
}


void ObjectRenderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	descriptor.Bind();
	store.GetIndexBuffer().Bind(GL_ELEMENT_ARRAY_BUFFER);

	store.UpdateScene(scene);

	for(const Object& object: scene.GetObjects())
	{
		const auto& model = store.GetModel(object.GetModelID());
		for(const auto& mesh: model.GetMeshes())
		{
			auto& material = store.GetMaterial(mesh.GetMaterialID());
			auto& program = store.GetProgram(material.GetProgramID());

			material.Bind(program);

			program->Use();

			program.SetModel(object.GetTransform());

			mesh.Draw();
		}
	}
}

} //namespace Render
