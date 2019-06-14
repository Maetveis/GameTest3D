#include "FrameParams.h"

#include "../Library/GL/Program.hpp"
#include "../Library/Logger/Logger.hpp"

void FrameParams::Bind(const GL::Program& program)
{
	Logger::Debug() << "Fp " << blockName << " " << program.GetUniformBlockIndex(blockName) << '\n';
	bindingPoint.AttachToBlock(program, program.GetUniformBlockIndex(blockName));
	bindingPoint.AttachBuffer(buffer);
}

void FrameParams::Update()
{
	buffer.BufferData(data, GL_DYNAMIC_DRAW);
}
