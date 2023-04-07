#pragma once
#include <memory>
#include <thread>

#include "Defines.h"
#include "LayerStack.h"
#include "../Window/Window.h"
#include "../Scene/Scene.h"

class Engine
{
private:
	inline static Engine* s_Instance = nullptr;

	bool m_IsRunning = true;

	std::unique_ptr<Window> m_Window;
	//Maybe change this and add SceneManager
	std::unique_ptr<Scene> m_Scene;
	LayerStack m_LayerStack;

public:
	void Run();
	void Render();

public:
	Engine();
	
	bool IsRunning() const;

	void AttachLayer(const std::shared_ptr<Layer>& layer);

	Window* GetWindow();

	//Maybe remove this later
	Scene* GetScene();

	static Engine& Get();

	friend int main();
};