#include "BlockRangeParam.hpp"

#include <Render/ProgramInterface/ProgramInterface.hpp>

#include <Library/GL/Range.hpp>

namespace Render
{

BlockRangeParam::BlockRangeParam
(
	const ProgramInterface& interface,
	const char* name,
	const GL::Buffer& _buffer,
	const GL::Range& _range
):
	buffer(_buffer),
	range(_range),
	blockIndex(interface.GetBindingIndex(name))
{
}

void BlockRangeParam::Bind(const ProgramInterface& interface)
{
	interface.GetBinding(blockIndex).AttachBufferRange(buffer, range);
}

} //namespace Render
