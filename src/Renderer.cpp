#include <iostream>
#include <algorithm>

#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::Init(int width, int height, uint32_t* p_pixels)
{
	Width = width;
	Height = height;
	pixels = p_pixels;
}

void Renderer::Render(const Scene &scene)
{
	ActiveScene = &scene;
	glm::vec3 color;
	
	for(int y = 0; y < Height; y++)
	{
		for(int x = 0; x < Width; x++)
		{
			color = PerPixel(glm::vec2((float)x/(float)Width, (float)y/(float)Height));
			pixels[y*Width+x] = int(color.r*255) << 16 | int(color.g*255) << 8 | int(color.b*255);
		}
	}
}

glm::vec3 Renderer::GetSkyColor(const Ray &ray)
{
	float t = 0.5 * (glm::normalize(ray.Direction).y + 1.0);
	return glm::vec3(1.0 - t, 1.0 - t, 1.0 - t) + glm::vec3(t * 0.5, t * 0.7, t * 1.0);
}

glm::vec3 Renderer::PerPixel(glm::vec2 coords)
{
	coords = coords * glm::vec2(2.0, 2.0) - glm::vec2(1.0, 1.0);

	Ray ray;

	ray.Origin = glm::vec3(0.0, 0.0, 2.0);
	ray.Direction = glm::vec3(coords, -2);

	Renderer::HitPayload payload = TraceRay(ray);

	if (payload.ObjectIndex < 0)
		return glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 lightDir = glm::normalize(glm::vec3(-1.0, -1.0, -1.0));

	float lightIndencity = glm::max(glm::dot(payload.WorldNormal, -lightDir), 0.0f);
	
	return ActiveScene->spheres[payload.ObjectIndex].Color * lightIndencity;
	// return payload.WorldNormal * 0.5f + glm::vec3(0.5f, 0.5f, 0.5f);
}

Renderer::HitPayload Renderer::TraceRay(const Ray &ray)
{
	int objectindex = -1;
	float closestHit = FLT_MAX;

	for (int i = 0; i < ActiveScene->spheres.size(); i++)
	{
		const Sphere &sphere = ActiveScene->spheres[i];
		glm::vec3 origin = ray.Origin - sphere.Center;
		
		float a = glm::dot(ray.Direction, ray.Direction);
		float b = 2 * glm::dot(origin, ray.Direction);
		float c = glm::dot(origin, origin) - sphere.Radius*sphere.Radius;
		float d = b*b - 4*a*c;
		
		if (d < 0.0)
			continue;

		float t = (-b - glm::sqrt(d)) / (2.0 * a);
		if (t > 0.0 && t < closestHit)
		{
			closestHit = t;
			objectindex = i;
		}
	}

	Renderer::HitPayload payload;
	payload.ObjectIndex = objectindex;
	payload.HitDistance = closestHit;

	if (objectindex < 0)
	{
		return payload;
	}

	Sphere ClosestSphere = ActiveScene->spheres[objectindex];

	glm::vec3 hitPoint = ray.Origin + ray.Direction * payload.HitDistance;
	payload.WorldNormal = glm::normalize(hitPoint - ClosestSphere.Center);

	return payload;
}