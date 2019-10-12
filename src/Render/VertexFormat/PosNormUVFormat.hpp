#ifndef RENDER_POSNORMUV_FORMAT_HPP
#define RENDER_POSNORMUV_FORMAT_HPP

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct PosNormUVFormat
{
	alignas(16) glm::vec3 pos;
	alignas(4) glm::vec3 norm;
	alignas(16) glm::vec2 uv;

	PosNormUVFormat(const glm::vec3& p, const glm::vec3& n, const glm::vec2& UV = glm::vec2(0,0)) :
		pos(p),
		norm(n),
		uv(UV)
	{
	}

	PosNormUVFormat(glm::vec3&& p, glm::vec3&& n, glm::vec2&& UV = glm::vec2(0,0)) :
		pos(p),
		norm(n),
		uv(UV)
	{
	}

	PosNormUVFormat() = default;

};

#endif //RENDER_POSNORMUV_FORMAT_HPP
