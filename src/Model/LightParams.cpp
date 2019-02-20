#include "LightParams.h"
#include "../Helper/ShaderProgram.h"

void LightParams::Update()
{
	buffer.BufferData(data, GL_STATIC_DRAW);
}

void LightParams::Bind(const ShaderProgram& program)
{
	bindingPoint.AttachToBlock(program, program.GetUniformBlockIndex(blockName));
	bindingPoint.AttachBuffer(buffer);
}
