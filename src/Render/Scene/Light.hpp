#ifndef RENDER_LIGHT_HPP
#define RENDER_LIGHT_HPP

#include <glm/vec3.hpp>

namespace Render
{

class Light
{
public:
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

} //namesapce Render

#endif //RENDER_LIGHT_HPP
