#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL/glew.h>
#include <string>
#include <memory>

#include "Shader.hpp"

namespace GL
{

class Program
{
private:
	GLuint programID;

	GLint GetInterfaceValue(GLenum programInterface, GLenum pname) const
	{
		GLint result;
		glGetProgramInterfaceiv(programID, programInterface, pname, &result);
		return result;
	}

	std::string GetResourceName(GLenum programInterface, GLint index) const
	{
		constexpr size_t BufferSize = 100;
		std::unique_ptr<char> buffer(new char[BufferSize]);
		GLint length;

		glGetProgramResourceName(programID, programInterface, index, BufferSize, &length, buffer.get());
		return std::string(buffer.get());
	}
public:
	Program() :
		programID(glCreateProgram())
	{
	}

	explicit Program(GLuint p) :
		programID(p)
	{
	}

	Program(Program&& other):
		programID(other.programID)
	{
		other.programID = 0;
	}

	Program(const Program&) = delete;

	~Program()
	{
		if(programID != 0)
			glDeleteProgram(programID);
	}

	Program& operator=(Program&& other)
	{
		std::swap(programID, other.programID);

		return *this;
	}

	GLuint Get() const
	{
		return programID;
	}

	GLuint GetId() const
	{
		return programID;
	}

	GLuint operator*() const
	{
		return programID;
	}

	operator bool ()
	{
		GLint result;
		glGetProgramiv(programID, GL_LINK_STATUS, &result);
		return result == GL_TRUE;
	}

	bool operator ! ()
	{
		GLint result;
		glGetProgramiv(programID, GL_LINK_STATUS, &result);
		return result != GL_TRUE;
	}

	GLuint GetUniformLocation(const char* name) const
	{
		return glGetUniformLocation(programID, name);
	}

	GLuint GetUniformBlockIndex(const char* name) const
	{
		return glGetUniformBlockIndex(programID, name);
	}

	GLuint GetShaderStorageBlockIndex(const char* name) const
	{
		return glGetProgramResourceIndex(programID, GL_SHADER_STORAGE_BLOCK, name);
	}

	GLint GetUniformCount() const
	{
		return GetInterfaceValue(GL_UNIFORM, GL_ACTIVE_RESOURCES);
	}

	GLint GetUniformBlockCount() const
	{
		return GetInterfaceValue(GL_UNIFORM_BLOCK, GL_ACTIVE_RESOURCES);
	}

	GLint GetShaderStorageBlockCount() const
	{
		return GetInterfaceValue(GL_SHADER_STORAGE_BLOCK, GL_ACTIVE_RESOURCES);
	}

	std::string GetUniformName(GLint index)
	{
		return GetResourceName(GL_UNIFORM, index);
	}

	std::string GetUniformBlockName(GLint index) const
	{
		return GetResourceName(GL_UNIFORM_BLOCK, index);
	}

	std::string GetShaderStorageBlockName(GLint index) const
	{
		return GetResourceName(GL_SHADER_STORAGE_BLOCK, index);
	}

	void AttachShader(const Shader& shader)
	{
		glAttachShader(programID, shader.GetId());
	}

	bool Link()
	{
		GLint result = GL_FALSE;

		glLinkProgram(programID);
		glGetProgramiv(programID, GL_LINK_STATUS, &result);

		return result == GL_TRUE;
	}

	void Use() const
	{
		glUseProgram(programID);
	}

	std::string GetInfoLog()
	{
		GLint infoLogLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

		auto errorMessage = std::make_unique<char[]>(infoLogLength);
		glGetProgramInfoLog(programID, infoLogLength, NULL, errorMessage.get());

		return std::string(errorMessage.get());
	}

	bool VsFsProgram( 	const std::string& vertexShaderName,
						const std::string& fragmentShaderName);
};

}// namespace GL;

#endif //PROGRAM_H
