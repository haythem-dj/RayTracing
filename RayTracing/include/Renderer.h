#pragma once

#include "Ray.h"
#include "Scene.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init(int width, int height, uint32_t* pixels);

	glm::vec3 GetSkyColor(const Ray &ray);

	void Render(const Camera& camera, const Scene &scene);

private:
	struct HitPayload
	{
		int ObjectIndex;
		float HitDistance;
		glm::vec3 WorldPosition;
		glm::vec3 WorldNormal;
	};

	glm::vec3 PerPixel(int x, int y);
	HitPayload TraceRay(const Ray &ray);
	HitPayload ClosestSphere(const Ray &ray, float hitDistance, int sphereIndex);
	HitPayload Miss(const Ray &ray);

private:
	int Width = 0, Height = 0;
	uint32_t* pixels = nullptr;

	const Scene* ActiveScene = nullptr;
	const Camera* ActiveCamera = nullptr;
};