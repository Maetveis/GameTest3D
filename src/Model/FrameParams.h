#ifndef FRAME_PARAMS_H
#define FRAME_PARAMS_H

#include "../Helper/UniformBuffer.h"

#include <glm/glm.hpp>

class ShaderProgram;

class FrameParams
{
public:
	void SetView(const glm::mat4 v)
	{
		data.view = v;
	}
	
	void SetProj(const glm::mat4 p)
	{
		data.proj = p;
	}
	
	const glm::mat4& GetView() const
	{
		return data.view;
	}
	
	const glm::mat4& GetProj() const 
	{
		return data.proj;
	}
	
	void Bind(const ShaderProgram& program);
	
	void Init();
	void Update();
private:
	struct Data
	{
		glm::mat4 view;
		glm::mat4 proj;
	};

	static constexpr const char* blockName = "FrameParams";

	UniformBuffer buffer;
	Data data;
};

#endif //FRAME_PARAMS_H