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
{
    glClearColor(0., 0., 0., 1.);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    descriptor.BindIndexBuffer(store.GetIndexBuffer());
    descriptor.BindVertexBuffer(store.GetVertexBuffer());


    GL::Shader tcs(GL_TESS_CONTROL_SHADER);
    if (!tcs.FromFile("../shaders/tcs-spheres.glsl")) {
        Logger::Error {} << "tcs-spheres.glsl Shader compilation failed: " << tcs.GetInfoLog() << '\n';
    }

    GL::Shader tes(GL_TESS_EVALUATION_SHADER);
    if (!tes.FromFile("../shaders/tes-spheres.glsl")) {
        Logger::Error {} << "tes-spheres.glsl Shader compilation failed: " << tes.GetInfoLog() << '\n';
    }

    GL::Shader vert(GL_VERTEX_SHADER);
    if (!vert.FromFile("../shaders/vert-spheres.glsl")) {
        Logger::Error {} << "vert-spheres.glsl Shader compilation failed: " << vert.GetInfoLog() << '\n';
    }

    GL::Shader frag(GL_FRAGMENT_SHADER);
    if (!frag.FromFile("../shaders/frag-spheres.glsl")) {
        Logger::Error {} << "frag-spheres.glsl Shader compilation failed: " << frag.GetInfoLog() << '\n';
    }

    spheresProgram.AttachShader(tcs);
    spheresProgram.AttachShader(tes);
    spheresProgram.AttachShader(vert);
    spheresProgram.AttachShader(frag);
    if (!spheresProgram.Link()) {
        Logger::Error{} << "Failed to link spheres program: " << spheresProgram.GetInfoLog() << '\n';    
    }
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

    spheresProgram.Use();
    glPatchParameteri(GL_PATCH_VERTICES, 1);
    glDrawArrays(GL_PATCHES, 0, 1000);

    glViewport(0, 0, width, height);

    lightPass.Execute(gBuffer, scene);
}

} //namespace Render
