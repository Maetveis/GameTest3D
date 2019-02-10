#ifndef MATERIAL_H

class Material
{
	virtual void BindNamed(ShaderProgram program) = 0;
	virtual void BindCurrent() = 0;

	virtual void ~Material()
	{
	}
}

#endif //MATERIAL_H
