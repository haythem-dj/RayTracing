#include "Camera.h"

Camera::Camera(float FOV, float nClip, float fClip)
	:FOV(FOV), nClip(nClip), fClip(fClip)
{
	Position = glm::vec3(0.0f, 0.0f, 3.0f);
	ForwardDirection = glm::vec3(0.0f, 0.0f, 0.0f);
}

Camera::~Camera()
{
}

void Camera::OnUpdate(float dt)
{
}

void Camera::OnResize(int width, int height)
{
}

void Camera::RecalculatePerspective()
{
}

void Camera::RecalculateView()
{
}

void Camera::RecalculateRayDirections()
{
}