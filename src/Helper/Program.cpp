#include "Program.hpp"

#include "Shader.hpp"

#include "../Log/Logger.h"

#include <fstream>
#include <memory>

namespace GL {

Program::Program(GLuint p) :
	programID(p)
{
}

void Program::CreateName()
{
	programID = glCreateProgram();
}

GLuint Program::GetUniformLocation(const char* name) const
{
	return glGetUniformLocation(programID, name);
}

GLuint Program::GetUniformBlockIndex(const char* name) const
{
	return glGetUniformBlockIndex(programID, name);
}

void Program::AttachShader(const Shader& shader)
{
	glAttachShader(programID, shader.GetId());
}

bool Program::Link()
{
	GLint result = GL_FALSE;

	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &result);

	return result == GL_TRUE;
}

std::string Program::GetInfoLog()
{
	GLint infoLogLength;
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

	std::unique_ptr<char> errorMessage(new char[infoLogLength]);
	glGetProgramInfoLog(programID, infoLogLength, NULL, errorMessage.get());

	//Logger::Debug << errorMessage << '\n';

	return std::string(errorMessage.get());
}

void Program::Use() const
{
	glUseProgram(programID);
}

void Program::Unuse() const
{
	glUseProgram(0);
}

void Program::Destroy()
{
	glDeleteProgram(programID);
}

bool Program::VsFsProgram( const std::string& vertexShaderName,
	const std::string& fragmentShaderName)
{
	Shader vertexShader(GL_VERTEX_SHADER);
	Shader fragmentShader(GL_FRAGMENT_SHADER);

	bool valid = true;
	if(!vertexShader.FromFile(vertexShaderName))
	{
		Logger::Error << "Vertex Shader Compilation failed:\n"
			<< vertexShader.GetInfoLog() << '\n';
		valid = false;
	}

	if(!fragmentShader.FromFile(fragmentShaderName))
	{
		Logger::Error << "Fragment Shader Compilation failed:\n"
			<< fragmentShader.GetInfoLog() << '\n';
		valid = false;
	}

	if(!valid)
	{
		Logger::Error << "Vertex Fragment program creation failed: Shader compilation failed\n";
		return false;
	}

	AttachShader(vertexShader);
	AttachShader(fragmentShader);
	if(!Link())
	{
		Logger::Error << "Vertex Fragment program creation failed: Linking failed:\n"
			<< GetInfoLog() << '\n';
	}

	return true;
}

}// namespace GL
