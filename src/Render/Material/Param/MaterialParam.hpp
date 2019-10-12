#ifndef RENDER_MATERIAL_PARAM_HPP
#define RENDER_MATERIAL_PARAM_HPP

namespace GL
{
class Program;
}

namespace Render
{
class ProgramInterface;
}

namespace Render
{

class MaterialParam
{
public:
	virtual void Bind( const ProgramInterface& interface) = 0;

	virtual ~MaterialParam() = default;
};

} //namespace Render

#endif //RENDER_MATERIAL_PARAM_HPP
