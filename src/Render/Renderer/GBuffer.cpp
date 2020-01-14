#include "GBuffer.hpp"

#include <Library/Logger/Logger.hpp>

namespace Render {

GBuffer::GBuffer(unsigned width, unsigned heigth)
{
    position.SetStorage(1, GL_RGBA32F, width, heigth);
    normal.SetStorage(1, GL_RGB16_SNORM, width, heigth);
    albedo.SetStorage(1, GL_RGB8, width, heigth);
    depth.SetStorage(1, GL_DEPTH_COMPONENT24, width, heigth);
	
	glTextureParameteri(depth.GetId(), GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTextureParameteri(depth.GetId(), GL_TEXTURE_COMPARE_FUNC, GL_LESS);

    frameBuffer.AttachTextureLevel(GL_COLOR_ATTACHMENT0, position, 0);
    frameBuffer.AttachTextureLevel(GL_COLOR_ATTACHMENT1, normal, 0);
    frameBuffer.AttachTextureLevel(GL_COLOR_ATTACHMENT2, albedo, 0);
    frameBuffer.AttachTextureLevel(GL_DEPTH_ATTACHMENT, depth, 0);

    frameBuffer.SetDrawBuffers({ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 });

    GLenum status = frameBuffer.CheckComplete(GL_DRAW_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        Logger::Error {} << "Unable to create Gbuffer\n";
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
        Logger::Info {} << "Gbuffer Created Sucessfully\n";
    }
}

void GBuffer::Resize(unsigned int width, unsigned int heigth)
{
}

}