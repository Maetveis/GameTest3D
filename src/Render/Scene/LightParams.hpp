#ifndef RENDER_LIGHT_PARAMS_HPP
#define RENDER_LIGHT_PARAMS_HPP

#include "Light.hpp"

#include "../../Library/GL/UniformBinding.hpp"
#include "../../Library/GL/Buffer.hpp"

#include <glm/glm.hpp>

namespace GL
{

class Program;

}

namespace Render
{

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

	void Bind(const GL::Program& program);

	void AddLight(const Light& light)
	{
		data.lights[data.lightCount++] = light;
	}
private:
	GL::UniformBinding bindingPoint;
	GL::Buffer buffer;

	struct Data
	{
		Light lights[10];
		unsigned int lightCount = 0;
	};
	Data data;
};

} //namespace Render

#endif //RENDER_LIGHT_PARAMS_HPP
