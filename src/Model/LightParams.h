#ifndef LIGHT_PARAMS_H
#define LIGHT_PARAMS_H

#include "../Helper/UniformBuffer.h"

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
	
	void Bind(const ShaderProgram& program);
	
	void Init();
private:
	static constexpr const char* blockName = "LightParams";

	UniformBuffer buffer;
	struct Data
	{
		Light lights[10];
		unsigned int lightCount;
	};
	Data data;
};

#endif //LIGHT_PARAMS_H