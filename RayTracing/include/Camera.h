#pragma once

#include <vector>

#include "glm/glm.hpp"

class Camera
{
public:
	Camera(float FOV, float nClip, float fClip);
	~Camera();

	void OnUpdate(float dt);
	void OnResize(int width, int height);

	const glm::mat4 &GetPerspective() const { return Perspective; }
	const glm::mat4 &GetInversePerspective() const { return InversePerspective; }
	const glm::mat4 &GetView() const { return View; }
	const glm::mat4 &GetInverseView() const { return InverseView; }

	const glm::vec3 &GetPosition() const { return Position; }
	const glm::vec3 &GetForwardDirection() const { return ForwardDirection; }

	const std::vector<glm::vec3> &GetRayDirections() const { return RayDirections; }

	float GetRotaionSpeed() const { return RotationSpeed; }

private:
	void RecalculatePerspective();
	void RecalculateView();
	void RecalculateRayDirections();

private:
	glm::mat4 Perspective {1.0f};
	glm::mat4 View {1.0f};
	glm::mat4 InversePerspective {1.0f};
	glm::mat4 InverseView {1.0f};

	float FOV = 45.0;
	float nClip = 0.1f;
	float fClip = 100.0f;

	glm::vec3 Position {0.0f};
	glm::vec3 ForwardDirection {0.0f};

	std::vector<glm::vec3> RayDirections;

	float RotationSpeed = 0.3f;

	glm::vec2 LastMousePosition {0.0f};

	int width = 0, height = 0;
};