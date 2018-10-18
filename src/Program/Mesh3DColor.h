#ifndef MESH_3D_COLOR_H
#define MESH_3D_COLOR_H

#include "../Helper/ShaderProgram.h"
#include "../Model/FrameParams.h"
#include "../Model/MaterialParams.h"
#include "../Model/LightParams.h"
#include "../Model/Mesh3D.h"

class Mesh3DColor
{
public:
	void Init();

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

	MaterialFormat& Material()
	{
		return material.Data();
	}

	const MaterialFormat& Material() const
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
		mesh.DrawAll();
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
