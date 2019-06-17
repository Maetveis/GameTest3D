#ifndef RENDER_OBJECT_HPP
#define RENDER_OBJECT_HPP

#include "../Model/RigidModel.hpp"

#include <glm/mat4x4.hpp>

namespace Render
{

class Object
{
public:
	RigidModel& model;
	glm::mat4 transform;

	Object(RigidModel& _model, const glm::mat4& _transform):
		model(_model),
		transform(_transform)
	{
	}
};

} //namespace Render

#endif //RENDER_OBJECT_HPP
