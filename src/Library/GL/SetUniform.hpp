#ifndef GL_SET_UNIFORM_HPP
#define GL_SET_UNIFORM_HPP

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glm/mat2x2.hpp>
#include <glm/mat2x3.hpp>
#include <glm/mat2x4.hpp>

#include <glm/mat3x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat3x4.hpp>

#include <glm/mat4x2.hpp>
#include <glm/mat4x3.hpp>
#include <glm/mat4x4.hpp>

#include <GL/glew.h>

namespace GL
{
class Program;
}

namespace GL
{

// float

void SetUniformProgram(const Program& program, GLuint location, float value);

void SetUniformActive(GLuint location, float value);

// vec2

void SetUniformProgram(const Program& program, GLuint location, const glm::vec2& value);

void SetUniformActive(GLuint location, glm::vec2 value);

//vec3

void SetUniformProgram(const Program& program, GLuint location, const glm::vec3& value);

void SetUniformActive(GLuint location, const glm::vec3& value);

//vec4

void SetUniformProgram(const Program& program, GLuint location, const glm::vec4& value);

void SetUniformActive(GLuint location, const glm::vec4& value);

//uint

void SetUniformProgram(const Program& program, GLuint location, GLuint value);

void SetUniformActive(GLuint location, GLuint value);

//int

void SetUniformProgram(const Program& program, GLuint location, GLint value);

void SetUniformActive(GLuint location, GLint value);

//matrix2

void SetUniformProgram(const Program& program, GLuint location, const glm::mat2& value);

void SetUniformActive(GLuint location, const glm::mat2& value);

//matrix2x3

void SetUniformProgram(const Program& program, GLuint location, const glm::mat2x3& value);

void SetUniformActive(GLuint location, const glm::mat2x3& value);

//matrix2x4

void SetUniformProgram(const Program& program, GLuint location, const glm::mat2x4& value);

void SetUniformActive(GLuint location, const glm::mat2x4& value);

//matrix3

void SetUniformProgram(const Program& program, GLuint location, const glm::mat3& value);

void SetUniformActive(GLuint location, const glm::mat3& value);

//matrix3x2

void SetUniformProgram(const Program& program, GLuint location, const glm::mat3x2& value);

void SetUniformActive(GLuint location, const glm::mat3x2& value);

//matrix3x4

void SetUniformProgram(const Program& program, GLuint location, const glm::mat3x4& value);

void SetUniformActive(GLuint location, const glm::mat3x4& value);

//matrix4

void SetUniformProgram(const Program& program, GLuint location, const glm::mat4& value);

void SetUniformActive(GLuint location, const glm::mat4& value);

//matrix4x2

void SetUniformProgram(const Program& program, GLuint location, const glm::mat4x2& value);

void SetUniformActive(GLuint location, const glm::mat4x2& value);

//matrix4x3

void SetUniformProgram(const Program& program, GLuint location, const glm::mat4x3& value);

void SetUniformActive(GLuint location, const glm::mat4x3& value);

} //namespace GL

#endif //GL_SET_UNIFORM_HPP
