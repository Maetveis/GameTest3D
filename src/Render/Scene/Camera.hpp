#ifndef RENDER_CAMERA_HPP
#define RENDER_CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

#include <cstdint>

namespace Render
{

class Camera {
public:
	enum class Sign : int8_t {
		Zero = 0,
		Positive = 1,
		Negative = -1
	};

	struct Direction {
		Sign forward;
		Sign strafe;

		float GetForward() const { return static_cast<float>(forward); }
		float GetStrafe() const { return static_cast<float>(strafe); }
	};

	Camera()
		: orientation()
		, translate(0.f, 0.f, 0.f)
	{
		view =
			glm::mat4_cast(orientation)
			* glm::translate(glm::mat4(1.0), translate);
	}

	Camera(const glm::quat& _orientation, const glm::vec3& _translate)
		: orientation(_orientation)
		, translate(_translate)
	{
		view =
			glm::mat4_cast(orientation)
			* glm::translate(glm::mat4(1.0), translate);
	}

	void UpdateView(const glm::vec2& pitchYaw);
	void UpdateLocation(double deltaTime, const Direction& dir);

	const glm::mat4& GetView() const {return view;}
private:
	glm::mat4 view;
	glm::quat orientation;
	glm::vec3 translate;
};

class CameraControls {
public:
	CameraControls()
		: pitchYaw(0.f, 0.f)
		, sensitivity(0.001f)
	{
		dir = {Camera::Sign::Zero, Camera::Sign::Zero};
	}

	void OnKeyPressed(char button)
	{
		switch(button)
		{
		case 'w':
			dir.forward = Camera::Sign::Positive;
			break;
		case 's':
			dir.forward = Camera::Sign::Negative;
			break;
		case 'a':
			dir.strafe = Camera::Sign::Negative;
			break;
		case 'd':
			dir.strafe = Camera::Sign::Positive;
			break;
		}
	}

	void OnKeyReleased(char button)
	{
		switch(button)
		{
		case 'w':
		case 's':
			dir.forward = Camera::Sign::Zero;
			break;
		case 'a':
		case 'd':
			dir.strafe = Camera::Sign::Zero;
			break;
		}
	}

	void OnMouseMove(int deltaX, int deltaY, bool pressed)
	{
		if(pressed) {
			pitchYaw += glm::vec2(-sensitivity * float(deltaY), sensitivity * float(deltaX));
		}
	}

	void Update(Camera& camera, double deltaTime)
	{
		camera.UpdateLocation(deltaTime, dir);
		camera.UpdateView(pitchYaw);

		pitchYaw.x = 0.f;
		pitchYaw.y = 0.f;
	}
private:
	Camera::Direction dir;
	glm::vec2 pitchYaw;
	float sensitivity;
};

}

#endif //RENDER_CAMERA_HPP
