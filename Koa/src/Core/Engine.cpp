#include <cmath>
#include <conio.h>

#include "Engine.h"
#include "Time.h"

#include "../Window/WindowsWindow.h"
#include "../Renderer/Renderer.h"

Engine::Engine()
	: m_Context(WindowContext::Windows)
{
	s_Instance = this;

	//auto consoleWindow = std::make_unique<ConsoleWindow>(500, 500);

	//int windowWidth = 500;
	//int windowHeight = 500;

	//consoleWindow->DisableCursor();
	//m_Window->SetFont(L"LHF Full Block", 1, 1);
	//consoleWindow->SetFont(L"Consolas", 2, 2);

	//consoleWindow->SetConsoleBufferSize({ short(windowWidth), short(windowHeight) });
	//consoleWindow->SetConsoleWindowSize({ 0, 0, short(windowWidth - 1), short(windowHeight - 1) });

	//m_Window = std::move(consoleWindow);
	m_Window = std::make_unique<WindowsWindow>(700, 700);
	m_Scene = std::make_unique<Scene>();

	//m_Window->DisableResize();
	//m_Window->DisableScrollBar();
	//ConsoleWindow window(800, 600);
	//WindowsWindow window(800, 600);
	//window.Update();

	m_Scene->Start();
}

Engine::Engine(int width, int height, int pixelWidth, int pixelHeight, WindowContext context)
	: m_Context(context)
{
	s_Instance = this;

	switch (m_Context)
	{
	case WindowContext::Console:
	{
		auto consoleWindow = std::make_unique<ConsoleWindow>(width, height, pixelWidth, pixelHeight);
		consoleWindow->DisableCursor();
		m_Window = std::move(consoleWindow);
		break;
	}
	case WindowContext::Windows:
		m_Window = std::make_unique<WindowsWindow>(width, height);
		break;
	}

	m_Scene = std::make_unique<Scene>();
	m_Scene->Start();

	Renderer::SetWindowContext(m_Window.get());
}

void Engine::Run()
{
	while (m_IsRunning)
	{
		Time::FrameStart();

	    m_Window->Clear();
		m_LayerStack.UpdateLayers();
		m_Scene->Update();
		m_Scene->Render();
		m_Window->Update();

		m_Window->SetTitle(std::to_wstring(1.0f / Time::DeltaTime()).data());
	}
}

void Engine::Render()
{
	while (m_IsRunning)
	{
		m_Window->Update();
	}
}

bool Engine::IsRunning() const
{
	return m_IsRunning;
}

void Engine::AttachLayer(const std::shared_ptr<Layer>& layer)
{
	m_LayerStack.PushLayer(layer);
}

Window* Engine::GetWindow()
{
	return m_Window.get();
}

Scene* Engine::GetScene()
{
	return m_Scene.get();
}

Engine::WindowContext Engine::GetWindowContext() const
{
	return m_Context;
}

Engine& Engine::Get()
{
	return *s_Instance;
}