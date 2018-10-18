#include "Mesh3DColor.h"

void Mesh3DColor::Init()
{
	frame.Init();
	material.Init();
	light.Init();
	
	program.Init();
	program.VsFsProgram(vertFileName, fragFileName);
	
	frame.Bind(program);
	material.Bind(program);
	light.Bind(program);
}