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

    lightParams.GetBinding().AttachToBlock(blitProgram, blitProgram.GetUniformBlockIndex("LightParams"));
}

void LightPass::Execute(const GBuffer& gBuffer, Scene& scene)
{
    GL::FrameBuffer::BindDefault(GL_FRAMEBUFFER);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gBuffer.GetPositionTexture().Bind(positionUnit);
    gBuffer.GetNormalTexture().Bind(normalUnit);
    gBuffer.GetAlbedoTexture().Bind(albedoUnit);
    gBuffer.GetDepthTexture().Bind(depthUnit);

    lightParams.Upload(scene.GetLights(), scene.GetView());

    blitProgram.Use();

    GL::SetUniformActive(positionLocation, positionUnit);
    GL::SetUniformActive(normalLocation, normalUnit);
    GL::SetUniformActive(albedoLocation, albedoUnit);
    GL::SetUniformActive(depthLocation, depthUnit);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

} //namespace Render
