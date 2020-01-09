#include "LightPass.hpp"
#include "Library/GL/SetUniform.hpp"

namespace Render {

LightPass::LightPass()
{
    blitProgram.VsFsProgram("../shaders/blitVert.glsl", "../shaders/blitFrag.glsl");

    positionLocation = blitProgram.GetUniformLocation("positionTexture");
    normalLocation = blitProgram.GetUniformLocation("normalTexture");
    albedoLocation = blitProgram.GetUniformLocation("albedoTexture");
    depthLocation = blitProgram.GetUniformLocation("depthTexture");

    lightPosLocation = blitProgram.GetUniformLocation("lightPos");
    lightColorLocation = blitProgram.GetUniformLocation("lightColor");
    lightStrengthLocation = blitProgram.GetUniformLocation("lightStrength");

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

    blitProgram.Use();

    GL::SetUniformActive(positionLocation, positionUnit);
    GL::SetUniformActive(normalLocation, normalUnit);
    GL::SetUniformActive(albedoLocation, albedoUnit);
    GL::SetUniformActive(depthLocation, depthUnit);

    for (const auto& light : scene.GetLights()) {
        GL::SetUniformActive(lightPosLocation, glm::vec3(scene.GetView() * glm::vec4(light.pos, 1)));
        GL::SetUniformActive(lightColorLocation, light.color);
        GL::SetUniformActive(lightStrengthLocation, light.strength);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}

} //namespace Render
