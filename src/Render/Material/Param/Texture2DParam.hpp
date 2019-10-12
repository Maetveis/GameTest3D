#ifndef RENDER_TEXTURE_2D_PARAM_HPP
#define RENDER_TEXTURE_2D_PARAM_HPP

#include "MaterialParam.hpp"

#include <Library/GL/Texture/Texture2D.hpp>
#include <Library/GL/Program.hpp>
#include <Library/GL/SetUniform.hpp>

#include <Library/StaticCounter.hpp>

#include <GL/glew.h>

namespace Render {

class Texture2DParam : public MaterialParam
{
private:
	GL::Texture2D texture;
	GLuint samplerLocation;

	StaticCounter<GLint, GL::Texture> unit;
public:
	Texture2DParam(const std::string& name, GL::Program& program, GL::Texture2D _texture) :
		texture(std::move(_texture)),
		samplerLocation(program.GetUniformLocation(name.c_str()))
	{
	}

	void Bind(const ProgramInterface& interface) override
	{
		texture.Bind(unit);
		GL::SetUniformActive(samplerLocation, unit);
	}
};

} //namespace Render

#endif //RENDER_TEXTURE_2D_PARAM_HPP
