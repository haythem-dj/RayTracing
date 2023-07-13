#include "HEngine.h"
#include "MyRenderer.h"

class MainLayer: public HEngine::Layer
{
public:
	MainLayer()
	{
		Width = HEngine::Application::Get().GetViewportWidth();
		Height = HEngine::Application::Get().GetViewportHeight();

		pixels = HEngine::Application::Get().GetRenderer().GetPixels();

		renderer.Init(Width, Height, pixels);

		{
			Sphere sphere;
			sphere.Center = glm::vec3(-1.0f, 0.0f, -4.0f);
			sphere.Radius = 0.5f;
			sphere.Color = glm::vec3(1.0f, 0.0f, 0.0f);
			scene.spheres.push_back(sphere);
		}

		// {
		// 	Sphere sphere;
		// 	sphere.Center = glm::vec3(0.5, 0.0, -4.0);
		// 	sphere.Radius = 1.0;
		// 	sphere.Color = glm::vec3(0.0, 1.0, 0.0);
		// 	scene.spheres.push_back(sphere);
		// }
	}

	~MainLayer()
	{}

	void OnResize(int width, int height) override
	{
		Width = width;
		Height = height;
		pixels = HEngine::Application::Get().GetRenderer().GetPixels();
	}

	void OnUpdate(float dt) override
	{
		renderer.Render(scene);
	}

private:
	int Width, Height;
	uint32_t* pixels;
	Renderer renderer;
	Scene scene;
};

HEngine::Application* CreateApplication()
{
	HEngine::Application* app = new HEngine::Application(500, 500);
	app->PushLayer(new MainLayer());
	return app;
}