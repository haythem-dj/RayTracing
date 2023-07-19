#pragma once

#include "Ray.h"
#include "Scene.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init(int width, int height, uint32_t* pixels);

	glm::vec3 GetSkyColor(const Ray &ray);
	

	void Render(const Scene &scene);

private:
	struct HitPayload
	{
		int ObjectIndex;
		float HitDistance;
		glm::vec3 WorldNormal;
	};

	glm::vec3 PerPixel(glm::vec2 coords);
	HitPayload TraceRay(const Ray &ray);

private:
	int Width, Height;
	uint32_t* pixels;

	const Scene *ActiveScene;
};