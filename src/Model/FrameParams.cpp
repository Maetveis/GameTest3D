#include "FrameParams.h"

#include "../Helper/ShaderProgram.h"
#include "../Log/Logger.h"

void FrameParams::Bind(const ShaderProgram& program)
{
	Logger::Debug << "Fp " << blockName << " " << program.GetUniformBlockIndex(blockName) << '\n';
	bindingPoint.AttachToBlock(program, program.GetUniformBlockIndex(blockName));
	bindingPoint.AttachBuffer(buffer);
}

void FrameParams::Update()
{
	buffer.BufferData(data, GL_DYNAMIC_DRAW);
}
