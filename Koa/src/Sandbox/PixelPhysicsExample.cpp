#include "PixelPhysicsExample.h"
#include "../Core/Engine.h"
#include "../Components/Transform.h"
#include "../Components/Physics/PixelPhysics.h"
#include "../Components/Renderers/PixelRenderer.h"
#include "../Core/Time.h"
#include "../Core/Input.h"

PixelPhysicsExample::PixelPhysicsExample()
	: m_Grid({ 0, 0 }, { 50, 50 })
{
	m_Scene = Engine::Get().GetScene();
}

void PixelPhysicsExample::OnUpdate()
{
	Window* window = Engine::Get().GetWindow();

	static bool isPressed = false;
	if (Input::IsKeyPressed(Key::Space) && !isPressed)
	{
		isPressed = true;

		Entity* newEntity = m_Scene->CreateEntity();
		Transform* transform = newEntity->GetTransform();
		transform->SetPosition({ 25, 25, 0 });

		newEntity->AddComponent<PixelRenderer>();
		PixelPhysics* physicsPixel = newEntity->AddComponent<PixelPhysics>();
		m_Grid.AddPhysicsPixel(physicsPixel);
	}
	else if (Input::IsKeyReleased(Key::Space) && isPressed)
	{
		isPressed = false;
	}

	m_Grid.Simulate();

	//Vector3f position = m_Entity->GetTransform()->GetPosition();
	//if (Input::IsKeyPressed(Key::W))
	//{
	//	position.y += 1.0f * Time::DeltaTime();
	//}
	//if (Input::IsKeyPressed(Key::S))
	//{
	//	position.y -= 1.0f * Time::DeltaTime();
	//}
	//if (Input::IsKeyPressed(Key::D))
	//{
	//	position.x += 1.0f * Time::DeltaTime();
	//}
	//if (Input::IsKeyPressed(Key::A))
	//{
	//	position.x -= 1.0f * Time::DeltaTime();
	//}
	//m_Entity->GetTransform()->SetPosition(position);

	//if (Input::IsMouseButtonPressed(MouseButton::ButtonLeft))
	//{
	//	Entity* newEntity = m_Scene->CreateEntity();
	//	newEntity->AddComponent<PixelRenderer>();
	//	newEntity->AddComponent<PixelPhysics>();

	//	Vector3f mousePosition = Input::GetMousePosition();
	//	//newEntity->GetTransform()->SetPosition(mousePosition);
	//}
}