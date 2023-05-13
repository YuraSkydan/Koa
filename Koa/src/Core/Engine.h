#pragma once
#include <memory>
#include <thread>

#include "Defines.h"
#include "LayerStack.h"
#include "../Window/ConsoleWindow.h"
#include "../Scene/Scene.h"

class Engine
{
public:
	enum class WindowContext
	{
		Console,
		Windows
	};

private:
	inline static Engine* s_Instance = nullptr;

	bool m_IsRunning = true;

	WindowContext m_Context;
	std::unique_ptr<Window> m_Window;
	//Maybe change this and add SceneManager
	std::unique_ptr<Scene> m_Scene;
	LayerStack m_LayerStack;

private:
	Engine();
	Engine(int width, int height, int pixelWidth, int pixelHeight, WindowContext context);

public:
	
	void Run();
	void Render();
	bool IsRunning() const;

	void AttachLayer(const std::shared_ptr<Layer>& layer);

	Window* GetWindow();
	//Maybe remove this later
	Scene* GetScene();

	WindowContext GetWindowContext() const;

	static Engine& Get();

	friend int main();
};