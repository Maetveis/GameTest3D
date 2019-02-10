#ifndef MATERIAL_PARAMS_H
#define MATERIAL_PARAMS_H

#include "../../Helper/UniformBuffer.h"
#include "ColorFormat.hpp"

class ShaderProgram;

class MaterialParams
{
public:
	MaterialParams() = default;

	ColorFormat& Data()
	{
		return data;
	}

	const ColorFormat& Data() const
	{
		return data;
	}

	void Init();
	void Bind(const ShaderProgram& program);
	void Update();
private:
	static constexpr const char* blockName = "MaterialParams";

	UniformBuffer buffer;
	ColorFormat data;
};

#endif //MATERIAL_PARAMS_H
