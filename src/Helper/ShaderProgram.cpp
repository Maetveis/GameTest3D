#include "ShaderProgram.h"

#include "../Log/Logger.h"

#include <fstream>

ShaderProgram::ShaderProgram(GLuint p) :
	programID(p)
{
}

void ShaderProgram::CreateName()
{
	programID = glCreateProgram();
}

GLuint ShaderProgram::GetUniformLocation(const char* name) const
{
	return glGetUniformLocation(programID, name);
}

GLuint ShaderProgram::GetUniformBlockIndex(const char* name) const
{
	return glGetUniformBlockIndex(programID, name);
}

void ShaderProgram::AttachShader(GLuint shaderID)
{
	glAttachShader(programID, shaderID);
}

bool ShaderProgram::Link()
{
	GLint result = GL_FALSE;

	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	if ( GL_FALSE == result )
	{
		Logger::Warning << "Shader linking failed." << '\n'
			<< GetInfoLog() << '\n';

		return false;
	} else {
		return true;
	}
}

std::string ShaderProgram::GetInfoLog()
{
	GLint infoLogLength;
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

	char* errorMessage = new char[infoLogLength];
	glGetProgramInfoLog(programID, infoLogLength, NULL, errorMessage);

	//Logger::Debug << errorMessage << '\n';

	std::string str(errorMessage);

	delete errorMessage;

	return str;
}

void ShaderProgram::Use() const
{
	glUseProgram(programID);
}

void ShaderProgram::Unuse() const
{
	glUseProgram(0);
}

void ShaderProgram::Destroy()
{
	glDeleteProgram(programID);
}

std::string ShaderProgram::ReadShader(const std::string& filename)
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

void ShaderProgram::VsFsProgram( const std::string& vertexShader,
	const std::string& fragmentShader)
{
	GLuint vertexID = CompileShader(GL_VERTEX_SHADER, ReadShader(vertexShader));
	GLuint fragmentID = CompileShader(GL_FRAGMENT_SHADER, ReadShader(fragmentShader));

	if(vertexID != 0 && fragmentID != 0)
	{
		AttachShader(vertexID);
		AttachShader(fragmentID);
		Link();
	}
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

GLuint ShaderProgram::CompileShader(const GLuint shaderType, const std::string& shaderCode)
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
}
