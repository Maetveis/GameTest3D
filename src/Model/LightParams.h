#ifndef LIGHT_PARAMS_H
#define LIGHT_PARAMS_H

#include "../Helper/UniformBuffer.h"
#include "../Helper/Buffer.hpp"

#include <glm/glm.hpp>

class ShaderProgram;

struct Light
{
	Light() = default;

	Light(const glm::vec3& p, const glm::vec3& c, float s) :
		pos(p),
		color(c),
		strength(s)
	{
	}

	union alignas(16)
	{
		glm::vec3 pos;
		glm::vec3 dir;
	};
	alignas(16) glm::vec3 color;
	float strength;
};

class LightParams
{
public:
	Light* Lights()
	{
		return data.lights;
	}

	void Update();

	void SetCount(unsigned int count)
	{
		data.lightCount = count;
	}

	unsigned int GetCount()
	{
		return data.lightCount;
	}

	void Bind(const ShaderProgram& program);
private:
	static constexpr const char* blockName = "LightParams";

	UniformBuffer bindingPoint;
	Buffer buffer;

	struct Data
	{
		Light lights[10];
		unsigned int lightCount = 1;
	};
	Data data;
};

#endif //LIGHT_PARAMS_H
