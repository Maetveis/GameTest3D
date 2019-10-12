#ifndef RENDER_UNIFORM_PARAM_HPP
#define RENDER_UNIFORM_PARAM_HPP

#include "MaterialParam.hpp"

#include <Library/GL/SetUniform.hpp>
#include <Library/GL/Program.hpp>

#include <glm/vec4.hpp>

#include <GL/glew.h>

namespace Render
{

template <typename T>
class UniformParam : public MaterialParam
{
private:
	GLuint location;
public:
	T value;

	UniformParam() = default;

	explicit UniformParam(GLuint _location, T _value = T()) :
		location(_location),
		value(_value)
	{
	}

	explicit UniformParam(const GL::Program& program, const char* name, T _value = T()) :
		location(program.GetUniformLocation(name)),
		value(_value)
	{
	}

	virtual void Bind(const ProgramInterface&) override
	{
		GL::SetUniformActive(location, value);
	}
};

} //namespace Render

#endif //RENDER_UNIFORM_PARAM_HPP
