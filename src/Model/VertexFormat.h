#ifndef VERTEX_FORMAT_H
#define VERTEX_FORMAT_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <GL/glew.h>
#include <cstddef>

struct VertexFormat
{
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 uv;

	VertexFormat(const glm::vec3& p, const glm::vec3& n, const glm::vec2& UV = glm::vec2(0,0)) :
		pos(p),
		norm(n),
		uv(UV)
	{
	}

	VertexFormat(glm::vec3&& p, glm::vec3&& n, glm::vec2&& UV = glm::vec2(0,0)) :
		pos(p),
		norm(n),
		uv(UV)
	{
	}

	static void SetGLAttributes(GLuint attributeID, GLuint vertexBufferID)
	{
		glBindVertexArray(attributeID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);


		//Set first attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

		//Set Second attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)sizeof(VertexFormat::pos));

		//Set Third attribute
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, uv));

		//Unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};

#endif //VERTEXT_FORMAT_H
