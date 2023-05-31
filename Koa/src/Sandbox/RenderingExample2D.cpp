#include "RenderingExample2D.h"
#include "../Core/Engine.h"
#include "../Core/Time.h"
#include "../Core/Input.h"
#include "../Components/Transform.h"
#include "../Components/Renderers/SpriteRenderer.h"
#include "../Components/Renderers/LineRenderer.h"
#include "../Components/Renderers/PixelRenderer.h"

RenderingExample2D::RenderingExample2D()
{
	srand(time(0));

	Engine& instance = Engine::Get();
	m_Scene = instance.GetScene();

	m_Entity = m_Scene->CreateEntity();
	m_Entity->AddComponent<SpriteRenderer>();
	//m_Entity->AddComponent<LineRenderer>();
}

void RenderingExample2D::OnAttach()
{

}

void RenderingExample2D::OnUpdate()
{
	Vector3f scale = m_Entity->GetTransform()->GetScale();
	Vector3f eulerAngles = m_Entity->GetTransform()->GetEulerAngles();

	Transform* transform = m_Entity->GetTransform();
	Vector3f position = transform->GetPosition();
	Vector3f angles = transform->GetEulerAngles();

	if (Input::IsKeyPressed(Key::D))
	{
		position.x += Time::DeltaTime();
	}
	if (Input::IsKeyPressed(Key::A))
	{
		position.x -= Time::DeltaTime();
	}
	if (Input::IsKeyPressed(Key::W))
	{
		position.y += Time::DeltaTime();
	}
	if (Input::IsKeyPressed(Key::S))
	{
		position.y -= Time::DeltaTime();
	}
	if (Input::IsKeyPressed(Key::Space))
	{
		angles.y += Time::DeltaTime() * 100;
	}

	transform->SetPosition(position);
	transform->SetEulerAngles(angles);

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
	
	window->DrawLine(t2[0], t2[1], Color::Red);
	window->DrawLine(t2[1], t2[2], Color::Red);
	window->DrawLine(t2[2], t2[0], Color::Red);
	
	//window->DrawVerticies(t0, Color::White);
	//window->DrawVerticies(t1, Color::Green);
	//window->DrawVerticies(t2, Color::Red);
	//window->DrawVerticies(std::vector<Vector2f>(square.begin(), square.begin() + 3), Color::Blue);
	//window->DrawVerticies(std::vector<Vector2f>(square.begin() + 3, square.end()), Color::Blue);
}