#ifndef RENDER_LIGHTPASS_HPP
#define RENDER_LIGHTPASS_HPP

#include "Library/StaticCounter.hpp"

#include "Library/GL/FrameBuffer.hpp"
#include "Library/GL/Program.hpp"
#include "Library/GL/Texture/Texture2D.hpp"

#include <GL/glew.h>

namespace Render {
class Scene;
class GBuffer;
}

namespace Render {

class LightPass {
public:
    LightPass(GBuffer& gBuffer);
    void Execute(const GBuffer& gBuffer, Scene& scene, const GL::Texture2D& ambientTexture);

private:
	GL::FrameBuffer frameBuffer;
	
	GL::Texture2D colorTexture;

	GL::Program spheresProgram;
	GL::Program ambientProgram;
	GL::Program blitProgram;

	//Gbuffer
    StaticCounter<GLint, GL::Texture> positionUnit;
    StaticCounter<GLint, GL::Texture> normalUnit;
    StaticCounter<GLint, GL::Texture> albedoUnit;
    StaticCounter<GLint, GL::Texture> depthUnit;

	//SSAO
	StaticCounter<GLint, GL::Texture> ambientUnit;
	
	StaticCounter<GLint, GL::Texture> colorUnit;

    GLuint positionLocation;
    GLuint normalLocation;
    GLuint albedoLocation;
    GLuint depthLocation;
	
	GLuint colorLocation;
};

} //namespace Render

#endif