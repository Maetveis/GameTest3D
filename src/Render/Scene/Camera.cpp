#include "Camera.hpp"

#include "Library/Logger/Logger.hpp"

namespace Render {

void Camera::UpdateView(const glm::vec2& pitchYaw)
{
	glm::quat yaw(glm::vec3(0.f, pitchYaw.y, 0.f));
	glm::quat pitch(glm::vec3(pitchYaw.x, 0.f, 0.f));

	orientation = glm::normalize(pitch * orientation * yaw);

	view =
		glm::mat4_cast(orientation)
		* glm::translate(glm::mat4(1.0), translate);
}

void Camera::UpdateLocation(double deltaTime, const Direction& dir)
{
	const float speed = 2;

	translate -=
		static_cast<float>(deltaTime) * speed *
			(- dir.GetForward() * glm::vec3(view[0].z, view[1].z, view[2].z)
		  	+ dir.GetStrafe() * glm::vec3(view[0].x, view[1].x, view[2].x));
}

} //namespace Render
