#ifndef RENDER_FRAME_PARAMS_H
#define RENDER_FRAME_PARAMS_H

#include <Library/GL/UniformBinding.hpp>
#include <Library/GL/Buffer.hpp>

#include <glm/glm.hpp>

namespace GL
{
	class Program;
}

namespace Render
{

class FrameParams
{
public:
	FrameParams()
	{
		bindingPoint.AttachBuffer(buffer);
	}

	void Upload(const glm::mat4& view, const glm::mat4 proj)
	{
		buffer.BufferData(Data{view, proj}, GL_STREAM_DRAW);
	}

	GL::UniformBinding& GetBinding()
	{
		return bindingPoint;
	}
private:
	struct Data
	{
		glm::mat4 view;
		glm::mat4 proj;
	};

	GL::UniformBinding bindingPoint;
	GL::Buffer buffer;
};

} //namespace Render

#endif //RENDER_FRAME_PARAMS_H
