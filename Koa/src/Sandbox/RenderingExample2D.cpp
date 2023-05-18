#include "RenderingExample2D.h"
#include "../Core/Engine.h"
#include "../Core/Time.h"
#include "../Components/Transform.h"
#include "../Components/Renderers/SpriteRenderer.h"
#include "../Components/Renderers/PixelRenderer.h"

RenderingExample2D::RenderingExample2D()
{
	srand(time(0));

	Engine& instance = Engine::Get();
	m_Scene = instance.GetScene();

	m_Entity = m_Scene->CreateEntity();
	m_Entity->AddComponent<SpriteRenderer>();
}

void RenderingExample2D::OnAttach()
{

}

void RenderingExample2D::OnUpdate()
{
	Vector3f scale = m_Entity->GetTransform()->GetScale();
	Vector3f eulerAngles = m_Entity->GetTransform()->GetEulerAngles();

	if (GetAsyncKeyState(VK_RIGHT))
	{
		scale.x += 1.0f * Time::DeltaTime();
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		scale.x -= 1.0f * Time::DeltaTime();
	}

	if (GetAsyncKeyState(VK_UP))
	{
		scale.y += 1.0f * Time::DeltaTime();
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		scale.y -= 1.0f * Time::DeltaTime();
	}

	if (GetAsyncKeyState(0x41))
	{
		eulerAngles.z += 50.0f * Time::DeltaTime();
	}
	else if(GetAsyncKeyState(0x44))
 	{
		eulerAngles.z -= 50.0f * Time::DeltaTime();
	}

	m_Entity->GetTransform()->SetEulerAngles(eulerAngles);
	m_Entity->GetTransform()->SetScale(scale);

	Window* window = Engine::Get().GetWindow();

	std::vector<Vector2f> t0
	{
		{ -0.9f, 0.0f },
		{ -0.4f, 0.1f },
		{ -0.6f, 0.8f }
	};

	std::vector<Vector2f> t1
	{ {  0.9f, -0.5f },
	  {  0.5f, -0.9f },
	  { -0.5f,  0.9f }
	};

	std::vector<Vector2f> t2
	{
		{ 0.9f, 0.6f },
		{ 0.2f, 0.7f },
		{ 0.3f, 0.9f }
	};

	std::vector<Vector2f> square
	{
		{ -0.5f, -0.5f },
		{ -0.5f,  0.5f },
		{  0.5f, -0.5f },

		{  0.5f, -0.5f },
		{  0.5f,  0.5f },
		{ -0.5f,  0.5f }
	};

	//window->DrawLine(t0[0], t0[1], Color::White);
	//window->DrawLine(t0[1], t0[2], Color::White);
	//window->DrawLine(t0[2], t0[0], Color::White);

	//window->DrawLine(t1[0], t1[1], Color::Green);
	//window->DrawLine(t1[1], t1[2], Color::Green);
	//window->DrawLine(t1[2], t1[0], Color::Green);
	
	//window->DrawLine(t2[0], t2[1], Color::Red);
	//window->DrawLine(t2[1], t2[2], Color::Red);
	//window->DrawLine(t2[2], t2[0], Color::Red);
	
	window->DrawVerticies(t0, Color::White);
	window->DrawVerticies(t1, Color::Green);
	window->DrawVerticies(t2, Color::Red);
	window->DrawVerticies(std::vector<Vector2f>(square.begin(), square.begin() + 3), Color::Blue);
	window->DrawVerticies(std::vector<Vector2f>(square.begin() + 3, square.end()), Color::Blue);
}