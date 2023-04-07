#include "RenderingExample.h"
#include "../Core/Engine.h"
#include "../Core/Time.h"
#include "../Components/Transform.h"
#include "../Components/Renderers/SpriteRenderer.h"
#include "../Components/Renderers/PixelRenderer.h"

RenderingExample::RenderingExample()
{
	srand(time(0));

	Engine& instance = Engine::Get();
	m_Scene = instance.GetScene();

	m_Entity = m_Scene->CreateEntity();
	m_Entity->AddComponent<SpriteRenderer>();
}

void RenderingExample::OnAttach()
{

}

void RenderingExample::OnUpdate()
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
}