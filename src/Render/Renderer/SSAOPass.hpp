#ifndef RENDER_SSAO_PASS_HPP
#define RENDER_SSAO_PASS_HPP

#include "Library/StaticCounter.hpp"

#include "Library/GL/Buffer.hpp"
#include "Library/GL/UniformBinding.hpp"
#include "Library/GL/FrameBuffer.hpp"
#include "Library/GL/Program.hpp"
#include "Library/GL/Texture/Texture2D.hpp"

#include <GL/glew.h>

#include <cstdint>

namespace Render {
class Scene;
class GBuffer;
}

namespace Render {

class SSAOPass {
public:
    SSAOPass(unsigned width, unsigned height, unsigned sampleCount);
    void Execute(const GBuffer& gBuffer, Scene& scene);
	const GL::Texture2D& GetAOMap(){ return aoMap; };

private:
	void GenerateKernel(unsigned sampleCount);
	void GenerateRotTexture(unsigned size);
	
	float sampleRadius;

	GL::FrameBuffer frameBuffer;
	
	GL::Texture2D aoMap;
	GL::Texture2D rotTexture;
	
	GL::Buffer kernelBuffer;
	GL::UniformBinding kernelBinding;
	
	GL::Program ssaoProgram;

    StaticCounter<GLint, GL::Texture> positionUnit;
    StaticCounter<GLint, GL::Texture> normalUnit;
    StaticCounter<GLint, GL::Texture> depthUnit;
    StaticCounter<GLint, GL::Texture> rotTextureUnit;

    GLuint positionLocation;
    GLuint normalLocation;
    GLuint depthLocation;
	GLuint rotTextureLocation;
	
	GLuint sampleRadiusLocation;
	
	GLuint projLocation;
};

} //namespace Render

#endif