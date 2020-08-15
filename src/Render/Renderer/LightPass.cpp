#include "LightPass.hpp"

#include "GBuffer.hpp"
#include "Render/Scene/Scene.hpp"

#include "Library/GL/SetUniform.hpp"

#include "Library/Logger/Logger.hpp"

namespace Render {

LightPass::LightPass(GBuffer& gbuffer)
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
	
	ambientProgram.VsFsProgram("../shaders/screenVert.glsl", "../shaders/ambientFrag.glsl");
	
	colorTexture.SetStorage(1, GL_R11F_G11F_B10F, 1000, 1000);
	frameBuffer.AttachTextureLevel(GL_COLOR_ATTACHMENT0, colorTexture, 0);
	frameBuffer.AttachTextureLevel(GL_DEPTH_ATTACHMENT, gbuffer.GetDepthTexture(), 0);
	frameBuffer.SetDrawBuffers({ GL_COLOR_ATTACHMENT0 });
	
	GLenum status = frameBuffer.CheckComplete(GL_DRAW_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        Logger::Error {} << "Unable to create LightBuffer\n";
        Logger::Error {} << "FrameBuffer is not complete for drawing\n";

        switch (status) {
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            Logger::Info {} << "Incomplete Attachment\n";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            Logger::Info {} << "No attachments\n";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            Logger::Info {} << "Inomplete Draw Buffer\n";
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            Logger::Info {} << "Incomplete Read Buffer\n";
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED:
            Logger::Info {} << "Unsuported Image formats\n";
            break;
        default:
            Logger::Info {} << "Other Incomplete status: " << status << '\n';
            break;
        }
    } else {
        Logger::Info {} << "LightBuffer Created Sucessfully\n";
    }
	
	blitProgram.VsFsProgram("../shaders/screenVert.glsl", "../shaders/blit.glsl");
	colorLocation = blitProgram.GetUniformLocation("colorTexture");
}

void LightPass::Execute(const GBuffer& gBuffer, Scene& scene, const GL::Texture2D& ambientTexture)
{
    frameBuffer.Bind(GL_DRAW_FRAMEBUFFER);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);

    gBuffer.GetPositionTexture().Bind(positionUnit);
    gBuffer.GetNormalTexture().Bind(normalUnit);
    gBuffer.GetAlbedoTexture().Bind(albedoUnit);
    gBuffer.GetDepthTexture().Bind(depthUnit);

	spheresProgram.Use();
	
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_FALSE);

    GL::SetUniformActive(positionLocation, positionUnit);
    GL::SetUniformActive(normalLocation, normalUnit);
    GL::SetUniformActive(albedoLocation, albedoUnit);
    GL::SetUniformActive(depthLocation, depthUnit);

    glPatchParameteri(GL_PATCH_VERTICES, 1);
    glDrawArrays(GL_PATCHES, 0, 25);
	
	glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	
	ambientTexture.Bind(ambientUnit);
	
	ambientProgram.Use();
	
	glCullFace(GL_BACK);
	
	GL::SetUniformActive(0, positionUnit);
	GL::SetUniformActive(1, ambientUnit);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	GL::FrameBuffer::BindDefault(GL_DRAW_FRAMEBUFFER);
	
	colorTexture.Bind(colorUnit);
	
	blitProgram.Use();
	
	GL::SetUniformActive(colorLocation, colorUnit);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);

    /*for (const auto& light : scene.GetLights()) {
        GL::SetUniformActive(lightPosLocation, glm::vec3(scene.GetView() * glm::vec4(light.pos, 1)));
        GL::SetUniformActive(lightColorLocation, light.color);
        GL::SetUniformActive(lightStrengthLocation, light.strength);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }*/
}

} //namespace Render
