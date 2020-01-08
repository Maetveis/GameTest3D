#ifndef RENDER_LIGHTPASS_HPP
#define RENDER_LIGHTPASS_HPP

#include "GBuffer.hpp"
#include "LightParams.hpp"

#include "Render/Scene/Scene.hpp"

#include "Library/StaticCounter.hpp"

#include "Library/GL/Program.hpp"
#include "Library/GL/Texture/Texture2D.hpp"

#include <GL/glew.h>

namespace Render {

class LightPass {
public:
    LightPass();
    void Execute(const GBuffer& gBuffer, Scene& scene);

private:
    GL::Program blitProgram;
    LightParams lightParams;

    StaticCounter<GLint, GL::Texture> positionUnit;
    StaticCounter<GLint, GL::Texture> normalUnit;
    StaticCounter<GLint, GL::Texture> albedoUnit;
    StaticCounter<GLint, GL::Texture> depthUnit;

    GLuint positionLocation;
    GLuint normalLocation;
    GLuint albedoLocation;
    GLuint depthLocation;
};

} //namespace Render

#endif