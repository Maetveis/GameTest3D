#ifndef RENDER_BLOCK_RANGE_PARAM_HPP
#define RENDER_BLOCK_RANGE_PARAM_HPP

#include "MaterialParam.hpp"

#include <Library/GL/Range.hpp>
#include <Library/GL/Buffer.hpp>

#include <memory>

#include <cstddef>

namespace Render
{
class ProgramInterface;
}

namespace GL
{
class Program;
class Buffer;
}

namespace Render
{

class BlockRangeParam : public MaterialParam
{
private:
	const GL::Buffer& buffer;
	GL::Range range;
	std::size_t blockIndex;
public:
	BlockRangeParam
	(
		const ProgramInterface& interface,
		const char* name,
		const GL::Buffer& buffer,
		const GL::Range& _range
	);

	virtual void Bind(const ProgramInterface& interface) override;
};

}

#endif //RENDER_BLOCK_RANGE_PARAM_HPP
