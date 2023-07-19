#include "Camera.h"

Camera::Camera(float FOV, float nClip, float fClip)
	:FOV(FOV), nClip(nClip), fClip(fClip)
{
	Position = glm::vec3(0.0f, 0.0f, 3.0f);
	ForwardDirection = glm::vec3(0.0f, 0.0f, 0.0f)
}

void Camera OnUpdate(float dt)
{}