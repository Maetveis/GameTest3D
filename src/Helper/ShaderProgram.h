#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>
#include <string>

class ShaderProgram
{
public:
	ShaderProgram() = default;

	void CreateName();

	explicit ShaderProgram(GLuint p);

	~ShaderProgram()
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

	void AttachShader(GLuint shaderID);
	bool Link();
	void Use() const;
	void Unuse() const;
	void Destroy();

	std::string GetInfoLog();

	void VsFsProgram( 	const std::string& vertexShader,
						const std::string& fragmentShader);

	static GLuint CompileShader(const GLuint shaderType, const std::string &shaderCode);
private:
	GLuint programID;

	static std::string ReadShader(const std::string& filename);
};

#endif //SHADER_PROGRAM_H
