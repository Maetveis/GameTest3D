#ifndef RENDER_OBJECT_HPP
#define RENDER_OBJECT_HPP

#include <Render/Model/RigidModel.hpp>

#include <glm/mat4x4.hpp>

namespace Render
{

class Object
{
private:
	size_t modelID;
	glm::mat4 transform;
public:

	Object(size_t _modelID, const glm::mat4& _transform):
		modelID(_modelID),
		transform(_transform)
	{
	}

	size_t GetModelID() const
	{
		return modelID;
	}

	const glm::mat4& GetTransform() const
	{
		return transform;
	}
};

} //namespace Render

#endif //RENDER_OBJECT_HPP
