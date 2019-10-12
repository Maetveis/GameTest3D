#include "ProgramInterface.hpp"

#include <Library/GL/Program.hpp>
#include <Library/Logger/Logger.hpp>

#include <utility>

namespace Render
{

ProgramInterface::ProgramInterface(GL::Program _program) :
	program(std::move(_program))
{
	for(
		int blockIndex = 0;
		blockIndex < program.GetUniformBlockCount();
		++blockIndex
	)
	{
		std::string blockName = program.GetUniformBlockName(blockIndex);
		if(blockName == "FrameParams")
		{
			frameIndex = blockIndex;
			Logger::Debug{} << "FrameParams: " << blockIndex << '\n';
			continue;
		}
		if(blockName == "LightParams")
		{
			lightIndex = blockIndex;
			Logger::Debug{} << "LightParams: " << blockIndex << '\n';
			continue;
		}


		bindings.emplace_back().AttachToBlock(program, blockIndex);
		bindingNames.emplace(program.GetUniformBlockName(blockIndex), bindings.size() - 1);
	}

	modelLocation = program.GetUniformLocation("model");
}

} //namespace Render
