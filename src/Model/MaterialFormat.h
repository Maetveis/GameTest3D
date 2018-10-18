#ifndef MATERIAL_FORMAT_H
#define MATERIAL_FORMAT_H

#include <glm/glm.hpp>
#include <GL/glew.h>

struct MaterialFormat
{
	alignas(16) glm::vec3 ambientColor;
	
	alignas(16) glm::vec3 diffuseColor;
	
	alignas(16) glm::vec3 specularColor;
	float specularExponent;
	
	MaterialFormat() = default;
	
	MaterialFormat(const glm::vec3& a, const glm::vec3& d, const glm::vec3& s, const float sE) :
		ambientColor(a),
		diffuseColor(d),
		specularColor(s),
		specularExponent(sE)
	{
	}
};

#endif //MATERIAL_FORMAT_H