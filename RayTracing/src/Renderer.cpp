#include <iostream>
#include <algorithm>
#include <chrono>

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

void Renderer::Render(const Camera &camera, const Scene &scene)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	ActiveScene = &scene;
	ActiveCamera = &camera;
	
	for(int y = 0; y < Height; y++)
	{
		for(int x = 0; x < Width; x++)
		{
			glm::vec3 color = PerPixel(x, y);
			pixels[y*Width+x] = int(color.r*255) << 16 | int(color.g*255) << 8 | int(color.b*255);
		}
	}
	end = std::chrono::system_clock::now();
	std::cout << std::chrono::duration<double>(end - start).count()*1000.0f << "\n";
}

glm::vec3 Renderer::GetSkyColor(const Ray &ray)
{
	//float t = 0.5f * (glm::normalize(ray.Direction).y + 1.0f);
	//return glm::vec3(1.0f - t, 1.0f - t, 1.0f - t) + glm::vec3(t * 0.5f, t * 0.7f, t * 1.0f);
	return glm::vec3(0.0f);
}

glm::vec3 Renderer::PerPixel(int x, int y)
{
	Ray ray;

	ray.Origin = ActiveCamera->GetPosition();
	ray.Direction = ActiveCamera->GetRayDirections()[y * Width + x];

	glm::vec3 color(0.0f);
	float multiplier = 1.0f;

	int bounces = 5;
	//int samples = 15;
	for (int i = 0; i < bounces; i++)
	{
		Renderer::HitPayload payload = TraceRay(ray);

		if (payload.HitDistance < 0.0f)
		{
			color += GetSkyColor(ray) * multiplier;
			break;
		}
		
		glm::vec3 lightDir = glm::normalize(glm::vec3(0.0f, 0.0f, -3.0f));
		float lightIndencity = glm::max(glm::dot(payload.WorldNormal, -lightDir), 0.0f);

		const Sphere& sphere = ActiveScene->spheres[payload.ObjectIndex];
		glm::vec3 sphereColor = sphere.Color;
		sphereColor *= lightIndencity;
		color += sphereColor * multiplier;

		multiplier *= 0.7f;

		ray.Origin = payload.WorldPosition + payload.WorldNormal * 0.0001f;
		ray.Direction = glm::reflect(ray.Direction, payload.WorldNormal);
	}

	return color;
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
		
		if (d < 0.0f)
			continue;

		float t = (-b - glm::sqrt(d)) / (2.0f * a);
		if (t > 0.0f && t < closestHit)
		{
			closestHit = t;
			objectindex = i;
		}
	}

	if (objectindex < 0)
		return Miss(ray);

	return ClosestSphere(ray, closestHit, objectindex);
}

Renderer::HitPayload Renderer::ClosestSphere(const Ray &ray, float hitDistance, int sphereIndex)
{
	Renderer::HitPayload payload;
	payload.ObjectIndex = sphereIndex;
	payload.HitDistance = hitDistance;

	Sphere ClosestSphere = ActiveScene->spheres[payload.ObjectIndex];

	payload.WorldPosition = ray.Origin + ray.Direction * payload.HitDistance;
	payload.WorldNormal = glm::normalize(payload.WorldPosition - ClosestSphere.Center);

	return payload;
}

Renderer::HitPayload Renderer::Miss(const Ray &ray)
{
	Renderer::HitPayload payload;
	payload.ObjectIndex = -1;
	payload.HitDistance = -1;

	return payload;
}
