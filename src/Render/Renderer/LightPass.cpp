#include "LightPass.hpp"
#include "Library/GL/SetUniform.hpp"

namespace Render {

LightPass::LightPass()
{
	GL::Shader vert(GL_VERTEX_SHADER);
    if (!vert.FromFile("../shaders/vert-spheres.glsl")) {
        Logger::Error {} << "vert-spheres.glsl Shader compilation failed: " << vert.GetInfoLog() << '\n';
    }
	
	GL::Shader tcs(GL_TESS_CONTROL_SHADER);
    if (!tcs.FromFile("../shaders/tcs-spheres.glsl")) {
        Logger::Error {} << "tcs-spheres.glsl Shader compilation failed: " << tcs.GetInfoLog() << '\n';
    }

    GL::Shader tes(GL_TESS_EVALUATION_SHADER);
    if (!tes.FromFile("../shaders/tes-spheres.glsl")) {
        Logger::Error {} << "tes-spheres.glsl Shader compilation failed: " << tes.GetInfoLog() << '\n';
    }


    GL::Shader frag(GL_FRAGMENT_SHADER);
    if (!frag.FromFile("../shaders/shade.glsl")) {
        Logger::Error {} << "shade.glsl Shader compilation failed: " << frag.GetInfoLog() << '\n';
    }

    spheresProgram.AttachShader(tcs);
    spheresProgram.AttachShader(tes);
    spheresProgram.AttachShader(vert);
    spheresProgram.AttachShader(frag);
    if (!spheresProgram.Link()) {
        Logger::Error{} << "Failed to link spheres program: " << spheresProgram.GetInfoLog() << '\n';    
    }

    positionLocation = spheresProgram.GetUniformLocation("positionTexture");
    normalLocation = spheresProgram.GetUniformLocation("normalTexture");
    albedoLocation = spheresProgram.GetUniformLocation("albedoTexture");
    depthLocation = spheresProgram.GetUniformLocation("depthTexture");
}

void LightPass::Execute(const GBuffer& gBuffer, Scene& scene)
{
    GL::FrameBuffer::BindDefault(GL_FRAMEBUFFER);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

    gBuffer.GetPositionTexture().Bind(positionUnit);
    gBuffer.GetNormalTexture().Bind(normalUnit);
    gBuffer.GetAlbedoTexture().Bind(albedoUnit);
    gBuffer.GetDepthTexture().Bind(depthUnit);

	spheresProgram.Use();

    GL::SetUniformActive(positionLocation, positionUnit);
    GL::SetUniformActive(normalLocation, normalUnit);
    GL::SetUniformActive(albedoLocation, albedoUnit);
    GL::SetUniformActive(depthLocation, depthUnit);


	spheresProgram.Use();
    glPatchParameteri(GL_PATCH_VERTICES, 1);
    glDrawArrays(GL_PATCHES, 0, 1000);
	
    /*for (const auto& light : scene.GetLights()) {
        GL::SetUniformActive(lightPosLocation, glm::vec3(scene.GetView() * glm::vec4(light.pos, 1)));
        GL::SetUniformActive(lightColorLocation, light.color);
        GL::SetUniformActive(lightStrengthLocation, light.strength);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }*/
}

} //namespace Render
