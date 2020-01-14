#include "ObjectRenderer.hpp"
#include "Library/GL/FrameBuffer.hpp"

#include "Render/ProgramInterface/ProgramInterface.hpp"
#include "Render/Scene/Object.hpp"
#include "Render/Scene/Scene.hpp"

#include "Library/GL/SetUniform.hpp"
#include "Library/GL/Shader.hpp"

#include "Library/Logger/Logger.hpp"

#include <GL/glew.h>

#include <iostream>

namespace Render {

ObjectRenderer::ObjectRenderer(Scene& _scene, RenderStore& _store)
    : scene(_scene)
    , store(_store)
    , gBuffer(1000, 1000)
	, ssaoPass(1000, 1000, 64)
	, lightPass(gBuffer)
{
    glClearColor(0., 0., 0., 1.);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
	
	glEnable(GL_FRAMEBUFFER_SRGB); 

    descriptor.BindIndexBuffer(store.GetIndexBuffer());
    descriptor.BindVertexBuffer(store.GetVertexBuffer());
}

void ObjectRenderer::ResizeViewPort(int newWidth, int newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
    width = newWidth;
    height = newHeight;
}

void ObjectRenderer::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
	
	glCullFace(GL_BACK);

    descriptor.Bind();
    store.GetIndexBuffer().Bind(GL_ELEMENT_ARRAY_BUFFER);

    store.UpdateScene(scene);

    glViewport(0, 0, 1000, 1000);

    gBuffer.BindDraw();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const Object& object : scene.GetObjects()) {
        const auto& model = store.GetModel(object.GetModelID());
        for (const auto& mesh : model.GetMeshes()) {
            auto& material = store.GetMaterial(mesh.GetMaterialID());
            auto& program = store.GetProgram(material.GetProgramID());

            material.Bind(program);

            program->Use();

            program.SetModel(object.GetTransform());

            mesh.Draw();
        }
    }

    glViewport(0, 0, width, height);
	
	ssaoPass.Execute(gBuffer, scene);

    lightPass.Execute(gBuffer, scene, ssaoPass.GetAOMap());
}

} //namespace Render
