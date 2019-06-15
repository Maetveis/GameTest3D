#ifndef MATERIAL_PARAMS_H
#define MATERIAL_PARAMS_H

#include "../../Library/GL/UniformBinding.hpp"
#include "../../DataStore/ManagedBuffer.hpp"

#include "ColorFormat.hpp"
#include "Material.hpp"

namespace GL {
	class Program;
}

class MaterialParams
{
public:
	MaterialParams() :
		uniformBuffer(30000, GL_STATIC_DRAW)
	{
	}

	void Bind(const GL::Program& program);

	size_t Push(const ColorFormat& material);

	void UseMaterial(size_t id);
private:
	static constexpr const char* blockName = "MaterialParams";

	std::vector<Material> materials;

	GL::UniformBinding uniformBinding;
	ManagedBuffer uniformBuffer;
};

#endif //MATERIAL_PARAMS_H
