#include "ShaderManager.h"

#include "../Log/Logger.h"

#include <utility>

//ASSERT
#include <cassert>

void ShaderManager::Destroy()
{
	for(auto& it : programs)
	{
		glDeleteProgram(it.second);
	}
}

const ShaderProgram& ShaderManager::Get(const std::string& name) const
{
	auto it = programs.find(name);
	assert(it != programs.end());
	
	return it->second;
}

ShaderProgram& ShaderManager::Get(const std::string& name)
{
	auto it = programs.find(name);
	assert(it != programs.end());
	
	return it->second;
}

ShaderProgram& ShaderManager::Create(const std::string& name)
{
	GLuint id = glCreateProgram();
	
	auto pair = programs.emplace(std::make_pair(name, id));
	return pair.first->second;
};

void ShaderManager::Remove(const std::string& name)
{
	auto it = programs.find(name);
	assert(it != programs.end());
	it->second.Destroy();
	programs.erase(it);
}

void ShaderManager::Use(const std::string& name) const
{
	Get(name).Use();
}

void ShaderManager::Unuse()
{
	glUseProgram(0);
}

/*
std::string ShaderManager::ReadShader(const std::string& filename)
{
	std::ifstream shaderStream(filename);
	if (!shaderStream.is_open())
	{
		Logger::Error << "Couldn't open shader file " << filename << '\n';
		return "";
	}
	
	//Copy the file to memory
	std::string shaderCode;
	shaderCode.assign(std::istreambuf_iterator<char>(shaderStream), std::istreambuf_iterator<char>());

	shaderStream.close();
	return shaderCode;
}

ShaderProgram& ShaderManager::CreateVsFsProgram(const std::string& name,
	const std::string& vertexShader,
	const std::string& fragmentShader)
{
	ShaderProgram& program = Create(name);
	
	GLuint vertexID = ShaderManager::CompileShader(GL_VERTEX_SHADER, ReadShader(vertexShader));
	GLuint fragmentID = ShaderManager::CompileShader(GL_FRAGMENT_SHADER, ReadShader(fragmentShader));
	
	if(vertexID != 0 && fragmentID != 0)
	{
		program.AttachShader(vertexID);
		program.AttachShader(fragmentID);
		
		program.Link();
	}
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	
	return program;
}
	
GLuint ShaderManager::CompileShader(const GLuint shaderType, const std::string& shaderCode)
{
	GLuint shaderID = glCreateShader(shaderType);
	if(shaderID == 0)
	{
		Logger::Warning << "Couldn't create shader" << '\n';
		return 0;
	}
	
	const char* str1[1];
	str1[0] = shaderCode.c_str();
	glShaderSource( shaderID, 1, str1, NULL );

	// Compile shader
	glCompileShader( shaderID );

	// Get Compilation status
	GLint result = GL_FALSE;
	
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if ( GL_FALSE == result )
	{
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		char* errorMessage = new char[infoLogLength];
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, errorMessage);

		Logger::Warning << "Shader Compilation failed" << '\n'
			<< errorMessage << '\n';
		
		glDeleteShader(shaderID);
		shaderID = 0;
	}

	return shaderID;
}*/