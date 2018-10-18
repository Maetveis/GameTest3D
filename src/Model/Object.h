#ifndfef OBJECT_H
#define OBJECT_H

class Object
{
	glm::vec3 pos;
	glm::vec3 rotation;
	float scale;
	
	void Draw(const glm::mat4& view, const glm::mat4& projection) const
	{
		glm::mat4 modelView = view * 
			glm::translate(pos) *
			glm::rotate({1.f, 0.f, 0.f}, rotation.x) *
			glm::rotate({0.f, 1.f, 0.f}, rotation.y) *
			glm::rotate({0.f, 0.f, 1.f}, rotation.z) *
			glm::scale(scale);
	}
};

#endif //OBJECT_H