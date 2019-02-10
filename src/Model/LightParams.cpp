#include "LightParams.h"
#include "../Helper/ShaderProgram.h"

void LightParams::Init()
{
}

void LightParams::Update()
{
	buffer.BufferData(data, GL_STATIC_DRAW);
}

void LightParams::Bind(const ShaderProgram& program)
{
	buffer.Bind(program, program.GetUniformBlockIndex(blockName));
}
