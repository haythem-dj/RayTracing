#include "Camera.h"

#include "HEvent.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(float FOV, float nClip, float fClip)
	:FOV(FOV), nClip(nClip), fClip(fClip)
{
	Position = glm::vec3(0.0f, 0.0f, 3.0f);
	ForwardDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	UpDirection = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera()
{
}

void Camera::OnUpdate(float dt)
{
	float speed = 5.0f;
	bool moved = false;

	if (HEngine::HEvent::IsKeyDown(HEngine::KeyCode::Z))
	{
		Position += ForwardDirection * speed * dt;
		moved = true;
	}
	else if (HEngine::HEvent::IsKeyDown(HEngine::KeyCode::S))
	{
		Position -= ForwardDirection * speed * dt;
		moved = true;
	}

	if (moved)
	{
		RecalculateView();
		RecalculateRayDirections();
	}
}

void Camera::OnResize(int width, int height)
{
	if (this->width == width && this->height == height)
		return;

	this->width = width;
	this->height = height;

	RecalculateProjection();
	RecalculateRayDirections();
}

void Camera::RecalculateProjection()
{
	Projection = glm::perspectiveFov(glm::radians(FOV), (float)width, (float)height, nClip, fClip);
	InverseProjection = glm::inverse(Projection);
}

void Camera::RecalculateView()
{
	View = glm::lookAt(Position, Position + ForwardDirection, UpDirection);
	InverseView = glm::inverse(View);
}

void Camera::RecalculateRayDirections()
{
	RayDirections.resize(width * height);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			glm::vec2 coord = { (float)x / (float)width, (float)y / (float)height };
			coord = coord * 2.0f - 1.0f;

			glm::vec4 target = InverseProjection * glm::vec4(coord.x, coord.y, 1.0f, 1.0f);
			glm::vec3 rayDirection = glm::vec3(InverseView * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0));
			RayDirections[y * width + x] = rayDirection;
		}
	}
}