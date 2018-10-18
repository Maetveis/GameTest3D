#include "MaterialParams.h"
#include "../Helper/ShaderProgram.h"

void MaterialParams::Init()
{
	buffer.Init();
}

void MaterialParams::Bind(const ShaderProgram& program)
{
	buffer.Bind(program, program.GetUniformBlockIndex(blockName));
}

void MaterialParams::Update()
{
	buffer.BufferData(data, GL_DYNAMIC_DRAW);
}