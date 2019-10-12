#ifndef RENDER_PROGRAM_INTERFACE_HPP
#define RENDER_PROGRAM_INTERFACE_HPP

#include <Render/Material/Param/BlockRangeParam.hpp>
#include <Render/Material/Param/UniformParam.hpp>

#include <Render/Material/Material.hpp>

#include <Library/GL/UniformBinding.hpp>
#include <Library/GL/Program.hpp>

#include <GL/glew.h>

#include <glm/mat4x4.hpp>

#include <map>
#include <vector>
#include <string>
#include <cstddef>
#include <string>

namespace GL
{
class Program;
}

namespace Render
{

class ProgramInterface
{
private:
	std::map< std::string, std::size_t> bindingNames;
	std::vector< GL::UniformBinding > bindings;

	GL::Program program;

	GLuint frameIndex;
	GLuint lightIndex;

	GLuint modelLocation;
public:
	explicit ProgramInterface(GL::Program program);

	std::size_t GetBindingIndex(const std::string& name) const
	{
		return bindingNames.at(name);
	}

	const GL::UniformBinding& GetBinding(std::size_t index) const
	{
		return bindings[index];
	}

	void AttachFrameLight(GL::UniformBinding& frameBinding, GL::UniformBinding& lightBinding)
	{
		frameBinding.AttachToBlock(program, frameIndex);
		lightBinding.AttachToBlock(program, lightIndex);
	}

	void SetModel(const glm::mat4& model)
	{
		GL::SetUniformActive(modelLocation, model);
	}

	GL::Program* operator->()
	{
		return &program;
	}

	GL::Program& operator*()
	{
		return program;
	}

	GL::Program& GetProgram()
	{
		return program;
	}
};


} //namespace Render

#endif //RENDER_PROGRAM_INTERFACE_HPP
