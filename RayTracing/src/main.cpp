#include "HEngine.h"
#include "Renderer.h"

class MainLayer: public HEngine::HLayer
{
public:
	MainLayer()
		:camera(45.0f, 0.1f, 100.0f)
	{
		Width = HEngine::HApplication::Get().GetViewportWidth();
		Height = HEngine::HApplication::Get().GetViewportHeight();

		pixels = HEngine::HApplication::Get().GetRenderer().GetPixels();

		camera.OnResize(Width, Height);
		renderer.Init(Width, Height, pixels);

		{
			Sphere sphere;
			sphere.Center = glm::vec3(-1.0f, 0.0f, -4.0f);
			sphere.Radius = 0.5f;
			sphere.Color = glm::vec3(1.0f, 0.0f, 0.0f);
			scene.spheres.push_back(sphere);
		}

		{
			Sphere sphere;
			sphere.Center = glm::vec3(1.0f, 0.0f, -4.0f);
			sphere.Radius = 0.5f;
			sphere.Color = glm::vec3(0.0f, 1.0f, 0.0f);
			scene.spheres.push_back(sphere);
		}
	}

	~MainLayer()
	{}

	void OnResize(int width, int height) override
	{
		Width = width;
		Height = height;
		pixels = HEngine::HApplication::Get().GetRenderer().GetPixels();
		camera.OnResize(width, height);
	}

	void OnUpdate(float dt) override
	{
		camera.OnUpdate(dt);
		renderer.Render(camera, scene);
	}

private:
	int Width, Height;
	uint32_t* pixels;
	Renderer renderer;
	Scene scene;
	Camera camera;
};

HEngine::HApplication* CreateApplication()
{
	HEngine::HApplication* app = new HEngine::HApplication(720, 480);
	app->PushLayer(new MainLayer());
	return app;
}