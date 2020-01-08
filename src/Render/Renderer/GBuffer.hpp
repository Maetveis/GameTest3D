#ifndef RENDER_GBUFFER_HPP
#define RENDER_GBUFFER_HPP

#include "Library/GL/FrameBuffer.hpp"
#include "Library/GL/Texture/Texture2D.hpp"

#include "Library/StaticCounter.hpp"

#include <GL/glew.h>

namespace Render {

class GBuffer {
public:
    GBuffer(unsigned _width, unsigned _height);

    void Resize(unsigned width, unsigned heigth);

    void BindDraw() { frameBuffer.Bind(GL_DRAW_FRAMEBUFFER); }

    void BindRead() { frameBuffer.Bind(GL_DRAW_FRAMEBUFFER); }

    void Bind() { frameBuffer.Bind(GL_FRAMEBUFFER); };

    const GL::Texture2D& GetPositionTexture() const { return position; };
    const GL::Texture2D& GetNormalTexture() const { return normal; };
    const GL::Texture2D& GetAlbedoTexture() const { return albedo; };
    const GL::Texture2D& GetDepthTexture() const { return depth; };

private:
    GL::Texture2D position;
    GL::Texture2D normal;
    GL::Texture2D albedo;
    GL::Texture2D depth;

    GL::FrameBuffer frameBuffer;
};

};

#endif