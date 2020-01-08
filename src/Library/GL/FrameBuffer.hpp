#ifndef FRAME_BUFFER_HPP
#define FRAME_BUFFER_HPP

#include <GL/glew.h>
#include <Library/GL/Texture/Texture.hpp>

#include <initializer_list>
#include <vector>

namespace GL {

class FrameBuffer {
public:
    FrameBuffer()
    {
        glCreateFramebuffers(1, &frameBuffer);
    }

    ~FrameBuffer()
    {
        glDeleteFramebuffers(1, &frameBuffer);
    }

    /*
    Possible Attachments of a framebuffer:
        - GL_COLOR_ATTACHMENTi i = (0..GL_MAX_COLOR_ATTACHMENTS) (min of 8)
        - GL_DEPTH_ATTACHMENT
        - GL_STENCIL_ATTACHMENT
        - GL_DEPTH_STENCIL_ATTACHMENT (both depth and stencil)
    */
    void AttachTextureLevel(GLenum attachment, const GL::Texture& texture, GLint level)
    {
        glNamedFramebufferTexture(frameBuffer, attachment, texture.GetId(), level);
    }

    void AtttachTextureLayer(GLenum attachment, const GL::Texture& texture, GLint level, GLint layer)
    {
        glNamedFramebufferTextureLayer(frameBuffer, attachment, texture.GetId(), level, layer);
    }

    /*
        Target of a FrameBuffer must be:
            - GL_DRAW_FRAMEBUFFER for rendering
            - GL_READ_FRAMEBUFFER for reading
            - GL_FRAMEBUFFER for both
    */
    void Bind(GLenum target)
    {
        glBindFramebuffer(target, frameBuffer);
    }

    GLenum CheckComplete(GLenum target)
    {
        return glCheckNamedFramebufferStatus(frameBuffer, target);
    }

    void SetDrawBuffers(const std::vector<GLenum>& attachments)
    {
        glNamedFramebufferDrawBuffers(frameBuffer, attachments.size(), attachments.data());
    }

    void SetDrawBuffers(std::initializer_list<GLenum> list)
    {
        glNamedFramebufferDrawBuffers(frameBuffer, list.size(), list.begin());
    }

    static void BindDefault(GLenum target)
    {
        glBindFramebuffer(target, 0);
    }

private:
    GLuint frameBuffer;
};

} //namespace GL

#endif