#include "FrameParams.h"

#include "../Helper/ShaderProgram.h"
#include "../Log/Logger.h"

void FrameParams::Bind(const ShaderProgram& program)
{
	Logger::Debug << "Fp " << blockName << " " << program.GetUniformBlockIndex(blockName) << '\n';
	buffer.Bind(program, program.GetUniformBlockIndex(blockName));
}

void FrameParams::Update()
{
	buffer.BufferData(data, GL_DYNAMIC_DRAW);
}
