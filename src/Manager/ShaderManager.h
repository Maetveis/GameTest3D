#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "../Helper/ShaderProgram.h"

#include <GL/glew.h>
#include <unordered_map>
#include <string>

class ShaderManager
{
private:
	std::unordered_map<std::string, ShaderProgram> programs;
public:
	ShaderManager() = default;

	ShaderProgram& Get(const std::string& name);
	const ShaderProgram& Get(const std::string& name) const;
	
	ShaderProgram& Create(const std::string& name);
	
	void Remove(const std::string& name);
	
	void Destroy();
	
	void Use(const std::string& name) const;
	void Unuse();
	
	ShaderProgram& CreateVsFsProgram(const std::string& name,
		const std::string& vertexShader,
		const std::string& fragmentShader)
	{
		ShaderProgram& program = Create(name);
		program.VsFsProgram(vertexShader, fragmentShader);
		return program;
	}
		
	static GLuint CompileShader(const GLuint shaderType, const std::string &shaderCode)
	{
		return ShaderProgram::CompileShader(shaderType, shaderCode);
	}
};

#endif //SHADER_MANAGER_H