#include <cmath>
#include <conio.h>

#include "Engine.h"
#include "Time.h"

//Remove later maybe 
#include "../Math/Vector2.h"

Engine::Engine()
{
	s_Instance = this;

	m_Window = std::make_unique<Window>();
	m_Scene = std::make_unique<Scene>();

	//m_Window->DisableCursor();
	//m_Window->SetFont(L"LHF Full Block", 1, 1);
	m_Window->SetFont(L"Consolas", 5, 5);

    int windowWidth = 200;
	int windowHeight = 200;
	
	m_Window->SetConsoleBufferSize({ short(windowWidth), short(windowHeight) });
	m_Window->SetConsoleWindowSize({ 0, 0, short(windowWidth - 1), short(windowHeight - 1) });
	
	//m_Window->DisableResize();
	//m_Window->DisableScrollBar();

	m_Scene->Start();
}

void Engine::Run()
{
	while (m_IsRunning)
	{
		Time::FrameStart();

		m_Window->ClearColor(Color::Black);
		m_LayerStack.UpdateLayers();
		m_Scene->Update();
		m_Scene->Render();
		m_Window->Update();

		m_Window->SetTitile(std::to_wstring(1.0f / Time::DeltaTime()).data());
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

Engine& Engine::Get()
{
	return *s_Instance;
}