#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL/glew.h>
#include <string>

namespace GL
{
	class Shader;
}

namespace GL
{

class Program
{
private:
	GLuint programID;
public:
	Program() = default;

	void CreateName();

	explicit Program(GLuint p);

	~Program()
	{
		Destroy();
	}

	GLuint Get() const
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

	GLuint GetUniformLocation(const char* name) const;
	GLuint GetUniformBlockIndex(const char* name) const;

	void AttachShader(const Shader& shader);
	bool Link();
	void Use() const;
	void Unuse() const;
	void Destroy();

	std::string GetInfoLog();

	bool VsFsProgram( 	const std::string& vertexShaderName,
						const std::string& fragmentShaderName);
};

}// namespace GL;

#endif //PROGRAM_H
