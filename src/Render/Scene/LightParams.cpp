#include "LightParams.hpp"
#include "../../Library/GL/Program.hpp"

namespace
{
	constexpr const char* BlockName = "LightParams";
}

namespace Render
{

void LightParams::Update()
{
	buffer.BufferData(data, GL_STATIC_DRAW);
}

void LightParams::Bind(const GL::Program& program)
{
	bindingPoint.AttachToBlock(program, program.GetUniformBlockIndex(BlockName));
	bindingPoint.AttachBuffer(buffer);
}

} //namespace Render
