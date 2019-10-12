#ifndef RENDER_MATERIAL_HPP
#define RENDER_MATERIAL_HPP

#include <Render/Material/Param/MaterialParam.hpp>

#include <vector>
#include <memory>

namespace Render
{

class Material
{
private:
	size_t programID;
	std::vector< std::unique_ptr<MaterialParam> > params;
public:
	Material(size_t _programID) :
		programID(_programID)
	{
	}

	Material(const Material&) = delete;

	Material(Material&& temp) :
		programID(temp.programID),
		params(std::move(temp.params))
	{
	}

	void AddParam(std::unique_ptr<MaterialParam> param)
	{
		params.emplace_back(std::move(param));
	}

	size_t GetProgramID() const
	{
		return programID;
	}

	void Bind(const ProgramInterface& programInterface) const
	{
		for(const auto& param : params)
		{
			param->Bind(programInterface);
		}
 	}
};

} //namespace Render

#endif //RENDER_MATERIAL_HPP
