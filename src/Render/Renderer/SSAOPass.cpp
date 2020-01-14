#include "SSAOPass.hpp"

#include "Gbuffer.hpp"
#include "Render/Scene/Scene.hpp"

#include "Library/GL/SetUniform.hpp"

#include "Library/Logger/Logger.hpp"

#include <glm/vec3.hpp>

#include <vector>
#include <random>

namespace {
struct RotData
{
	alignas(16) glm::vec3 vec;
};

float lerp(float a, float b, float x)
{
	return a + x * (b - a);
}

}

namespace Render {

SSAOPass::SSAOPass(unsigned width, unsigned height, unsigned sampleCount)
	: sampleRadius(.05f)
{
	ssaoProgram.VsFsProgram("../shaders/screenVert.glsl", "../shaders/ssaoFrag.glsl");

    positionLocation = ssaoProgram.GetUniformLocation("positionTexture");
    normalLocation = ssaoProgram.GetUniformLocation("normalTexture");
    depthLocation = ssaoProgram.GetUniformLocation("depthTexture");
	rotTextureLocation = ssaoProgram.GetUniformLocation("rotTexture");
	
	sampleRadiusLocation = ssaoProgram.GetUniformLocation("sampleRadius");

	projLocation = ssaoProgram.GetUniformLocation("proj");
	
	constexpr unsigned RotTextureSize = 4;
	
	aoMap.SetStorage(1, GL_R8, width, height);
	rotTexture.SetStorage(1, GL_RG16_SNORM, RotTextureSize, RotTextureSize);
	
	frameBuffer.AttachTextureLevel(GL_COLOR_ATTACHMENT0, aoMap, 0);
	frameBuffer.SetDrawBuffers({ GL_COLOR_ATTACHMENT0 });
	
	GLenum status = frameBuffer.CheckComplete(GL_DRAW_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        Logger::Error {} << "Unable to create SSAO framebuffer\n";
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
        Logger::Info {} << "SSAO Buffer Created Sucessfully\n";
    }
	
	Logger::Debug {} << "SSAO Init1\n";
	
	kernelBinding.AttachBuffer(kernelBuffer);
	
	Logger::Debug {} << "SSAO Init2\n";
	
	kernelBinding.AttachToBlock(ssaoProgram, ssaoProgram.GetUniformBlockIndex("KernelBlock"));
	
	Logger::Debug {} << "SSAO Init3\n";
	
	GenerateKernel(sampleCount);
	
	Logger::Debug {} << "SSAO Init4\n";
	
	GenerateRotTexture(RotTextureSize);
	
	Logger::Debug {} << "SSAO Init Finished\n";
}

void SSAOPass::Execute(const GBuffer& gBuffer, Scene& scene)
{
    frameBuffer.Bind(GL_DRAW_FRAMEBUFFER);

    glClear(GL_COLOR_BUFFER_BIT);

    gBuffer.GetPositionTexture().Bind(positionUnit);
    gBuffer.GetNormalTexture().Bind(normalUnit);
    gBuffer.GetDepthTexture().Bind(depthUnit);
	
	rotTexture.Bind(rotTextureUnit);
	
	glDisable(GL_DEPTH_TEST);

	ssaoProgram.Use();

    GL::SetUniformActive(positionLocation, positionUnit);
    GL::SetUniformActive(normalLocation, normalUnit);
    GL::SetUniformActive(depthLocation, depthUnit);
	GL::SetUniformActive(rotTextureLocation, rotTextureUnit);
	
	GL::SetUniformActive(sampleRadiusLocation, sampleRadius);
	GL::SetUniformActive(projLocation, scene.GetProj());
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void SSAOPass::GenerateKernel(unsigned sampleCount)
{
	std::minstd_rand gen;
	std::uniform_real_distribution<float> dist(0.f, 1.f);
	std::vector<RotData> samples;
	samples.reserve(sampleCount);
	for(uint32_t i = 0; i < sampleCount; ++i){
		glm::vec3 sample;
		do{
			sample.x = 2.f * dist(gen) - 1.f;
			sample.y = dist(gen);
			sample.z = 2.f * dist(gen) - 1.f;
		} while(length(sample) > 1.f);
		sample = glm::normalize(sample) * lerp(0.1f, 1.f, dist(gen));
		samples.push_back({sample});
	}
	
	kernelBuffer.BufferData(samples, GL_STATIC_DRAW);
}

void SSAOPass::GenerateRotTexture(unsigned size)
{
	std::minstd_rand gen(5);
	std::uniform_int_distribution<int16_t> dist(-32767, 32767);
	std::vector<int16_t> rotVectors;
	rotVectors.reserve(2 * size * size);
	
	for(unsigned i = 0; i < size * size; ++i){
		rotVectors.push_back(dist(gen));
		rotVectors.push_back(dist(gen));
	}
	rotTexture.SubImageData(0, 0, 0, size, size, GL_RG, GL_SHORT, rotVectors.data());
}

} //namespace Render
