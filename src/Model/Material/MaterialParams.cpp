#include "MaterialParams.h"

#include "../../Library/GL/Program.hpp"
#include "../../Library/GL/Range.hpp"

void MaterialParams::Bind(const GL::Program& program)
{
	uniformBinding.AttachToBlock(program, program.GetUniformBlockIndex(blockName));
}

size_t MaterialParams::Push(const ColorFormat& material)
{
	GL::Range range = uniformBuffer.Push(material, sizeof(ColorFormat));

	materials.emplace_back(range);

	return materials.size() - 1;
}

void MaterialParams::UseMaterial(size_t id)
{
	uniformBinding.AttachBufferRange(uniformBuffer, materials[id].GetLocation());
}
