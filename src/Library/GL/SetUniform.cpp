#include "SetUniform.hpp"

#include <Library/GL/Program.hpp>

namespace GL
{

// float

void SetUniformProgram(const Program& program, GLuint location, float value)
{
	glProgramUniform1f(program.GetId(), location, value);
}

void SetUniformActive(GLuint location, float value)
{
	glUniform1f(location, value);
}

// vec2

void SetUniformProgram(const Program& program, GLuint location, const glm::vec2& value)
{
	glProgramUniform2fv(program.GetId(), location, 1, &value[0]);
}

void SetUniformActive(GLuint location, glm::vec2 value)
{
	glUniform2fv(location, 1, &value[0]);
}

//vec3

void SetUniformProgram(const Program& program, GLuint location, const glm::vec3& value)
{
	glProgramUniform3fv(program.GetId(), location, 1, &value[0]);
}

void SetUniformActive(GLuint location, const glm::vec3& value)
{
	glUniform3fv(location, 1, &value[0]);
}

//vec4

void SetUniformProgram(const Program& program, GLuint location, const glm::vec4& value)
{
	glProgramUniform4fv(program.GetId(), location, 1, &value[0]);
}

void SetUniformActive(GLuint location, const glm::vec4& value)
{
	glUniform4fv(location, 1, &value[0]);
}

//uint

void SetUniformProgram(const Program& program, GLuint location, GLuint value)
{
	glProgramUniform1ui(program.GetId(), location, value);
}

void SetUniformActive(GLuint location, GLuint value)
{
	glUniform1ui(location, value);
}

//int

void SetUniformProgram(const Program& program, GLuint location, GLint value)
{
	glProgramUniform1i(program.GetId(), location, value);
}

void SetUniformActive(GLuint location, GLint value)
{
	glUniform1i(location, value);
}

//matrix2

void SetUniformProgram(const Program& program, GLuint location, const glm::mat2& value)
{
	glProgramUniformMatrix2fv(program.GetId(), location, 1, false, &value[0][0]);
}

void SetUniformActive(GLuint location, const glm::mat2& value)
{
	glUniformMatrix2fv(location, 1, false, &value[0][0]);
}

//matrix2x3

void SetUniformProgram(const Program& program, GLuint location, const glm::mat2x3& value)
{
	glProgramUniformMatrix2x3fv(program.GetId(), location, 1, false, &value[0][0]);
}

void SetUniformActive(GLuint location, const glm::mat2x3& value)
{
	glUniformMatrix2x3fv(location, 1, false, &value[0][0]);
}

//matrix2x4

void SetUniformProgram(const Program& program, GLuint location, const glm::mat2x4& value)
{
	glProgramUniformMatrix2x4fv(program.GetId(), location, 1, false, &value[0][0]);
}

void SetUniformActive(GLuint location, const glm::mat2x4& value)
{
	glUniformMatrix2x4fv(location, 1, false, &value[0][0]);
}

//matrix3

void SetUniformProgram(const Program& program, GLuint location, const glm::mat3& value)
{
	glProgramUniformMatrix3fv(program.GetId(), location, 1, false, &value[0][0]);
}

void SetUniformActive(GLuint location, const glm::mat3& value)
{
	glUniformMatrix3fv(location, 1, false, &value[0][0]);
}

//matrix3x2

void SetUniformProgram(const Program& program, GLuint location, const glm::mat3x2& value)
{
	glProgramUniformMatrix3x2fv(program.GetId(), location, 1, false, &value[0][0]);
}

void SetUniformActive(GLuint location, const glm::mat3x2& value)
{
	glUniformMatrix3x2fv(location, 1, false, &value[0][0]);
}

//matrix3x4

void SetUniformProgram(const Program& program, GLuint location, const glm::mat3x4& value)
{
	glProgramUniformMatrix3x4fv(program.GetId(), location, 1, false, &value[0][0]);
}

void SetUniformActive(GLuint location, const glm::mat3x4& value)
{
	glUniformMatrix3x4fv(location, 1, false, &value[0][0]);
}

//matrix4

void SetUniformProgram(const Program& program, GLuint location, const glm::mat4& value)
{
	glProgramUniformMatrix4fv(program.GetId(), location, 1, false, &value[0][0]);
}

void SetUniformActive(GLuint location, const glm::mat4& value)
{
	glUniformMatrix4fv(location, 1, false, &value[0][0]);
}

//matrix4x2

void SetUniformProgram(const Program& program, GLuint location, const glm::mat4x2& value)
{
	glProgramUniformMatrix4x2fv(program.GetId(), location, 1, false, &value[0][0]);
}

void SetUniformActive(GLuint location, const glm::mat4x2& value)
{
	glUniformMatrix4x2fv(location, 1, false, &value[0][0]);
}

//matrix4x3

void SetUniformProgram(const Program& program, GLuint location, const glm::mat4x3& value)
{
	glProgramUniformMatrix4x3fv(program.GetId(), location, 1, false, &value[0][0]);
}

void SetUniformActive(GLuint location, const glm::mat4x3& value)
{
	glUniformMatrix4x3fv(location, 1, false, &value[0][0]);
}

} //namespace GL
