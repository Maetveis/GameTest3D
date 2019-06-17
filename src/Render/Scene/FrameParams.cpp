#include "FrameParams.hpp"

#include "../../Library/GL/Program.hpp"
#include "../../Library/Logger/Logger.hpp"

namespace
{
	constexpr const char* BlockName = "FrameParams";
}

namespace Render
{

void FrameParams::Bind(const GL::Program& program)
{
	Logger::Debug() << "Fp " << BlockName << " " << program.GetUniformBlockIndex(BlockName) << '\n';
	bindingPoint.AttachToBlock(program, program.GetUniformBlockIndex(BlockName));
	bindingPoint.AttachBuffer(buffer);
}

void FrameParams::Update()
{
	buffer.BufferData(data, GL_DYNAMIC_DRAW);
}

} //namespace Render
