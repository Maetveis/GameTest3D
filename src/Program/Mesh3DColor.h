#ifndef MESH_3D_COLOR_H
#define MESH_3D_COLOR_H

#include "../Helper/ShaderProgram.h"
#include "../Model/FrameParams.h"
#include "../Model/Material/MaterialParams.h"
#include "../Model/LightParams.h"
#include "../Model/Mesh/Mesh3D.hpp"

class Mesh3DColor
{
public:
	void Init();

	Mesh3DColor();

	void SetView(const glm::mat4 v)
	{
		frame.SetView(v);
	}

	void SetProj(const glm::mat4 p)
	{
		frame.SetProj(p);
	}

	const glm::mat4& GetView() const
	{
		return frame.GetView();
	}

	const glm::mat4& GetProj() const
	{
		return frame.GetProj();
	}

	Light* Lights()
	{
		return light.Lights();
	}

	void Update()
	{
		frame.Update();
		material.Update();
		light.Update();
	}

	ColorFormat& Material()
	{
		return material.Data();
	}

	const ColorFormat& Material() const
	{
		return material.Data();
	}


	void Use()
	{
		program.Use();
	}

	void Unuse()
	{
		program.Unuse();
	}

	void Render(Mesh3D& mesh)
	{
		mesh.Draw();
	};

	ShaderProgram& Program()
	{
		return program;
	}

private:
	static constexpr const char* vertFileName = "../shaders/blinPhongVert.glsl";
	static constexpr const char* fragFileName = "../shaders/blinPhongFrag.glsl";

	FrameParams frame;
	MaterialParams material;
	LightParams light;
	ShaderProgram program;
};

#endif //MESH_3D_COLOR_H
