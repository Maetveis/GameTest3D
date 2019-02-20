#ifndef MATERIAL_PARAMS_H
#define MATERIAL_PARAMS_H

#include "../../Helper/UniformBuffer.h"
#include "../../DataStore/ManagedBuffer.hpp"

#include "ColorFormat.hpp"
#include "Material.hpp"

class ShaderProgram;

class MaterialParams
{
public:
	MaterialParams() :
		buffer(30000, GL_STATIC_DRAW)
	{
	}

	void Bind(const ShaderProgram& program);

	size_t Push(const ColorFormat& material);

	void UseMaterial(size_t id);
private:
	static constexpr const char* blockName = "MaterialParams";

	std::vector<Material> materials;

	UniformBuffer bindingIndex;
	ManagedBuffer buffer;
};

#endif //MATERIAL_PARAMS_H
