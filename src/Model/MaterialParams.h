#ifndef MATERIAL_PARAMS_H
#define MATERIAL_PARAMS_H

#include "../Helper/UniformBuffer.h"
#include "MaterialFormat.h"

class ShaderProgram;

class MaterialParams
{
public:
	MaterialParams() = default;
	
	MaterialFormat& Data()
	{
		return data;
	}
	
	const MaterialFormat& Data() const
	{
		return data;
	}
	
	void Init();
	void Bind(const ShaderProgram& program);
	void Update();
private:
	static constexpr const char* blockName = "MaterialParams";

	UniformBuffer buffer;
	MaterialFormat data;
};

#endif //MATERIAL_PARAMS_H