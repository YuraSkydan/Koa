#include "PhysicsExample.h"
#include "../Core/Engine.h"

#include "../Components/Transform.h"
#include "../Components/Renderers/SpriteRenderer.h"
#include "../Components/Physics/Rigidbody.h"
#include "../Components/Physics/BoxCollider.h"

PhysicsExample::PhysicsExample()
{
	m_Scene = Engine::Get().GetScene();

	Entity* box_1 = m_Scene->CreateEntity();
	box_1->AddComponent<SpriteRenderer>();

	box_1->GetTransform()->SetPosition(Vector3f(0.0f, 0.5f, 0.0f));
	box_1->GetTransform()->SetEulerAngles(Vector3f(0.0f, 0.0f, 30.0f));
	box_1->GetTransform()->SetScale(Vector3f(0.3f, 0.3f, 0.0f));

	box_1->AddComponent<BoxCollider>();
	box_1->AddComponent<Rigidbody>();

	Entity* box_2 = m_Scene->CreateEntity();
	box_2->AddComponent<SpriteRenderer>();

	box_2->GetTransform()->SetPosition(Vector3f(0.0f, 2.0f, 0.0f));
	box_2->GetTransform()->SetEulerAngles(Vector3f(0.0f, 0.0f, 0.0f));
	box_2->GetTransform()->SetScale(Vector3f(0.3f, 0.3f, 0.0f));

	box_2->AddComponent<BoxCollider>();
	box_2->AddComponent<Rigidbody>();

	Entity* platform = m_Scene->CreateEntity();
	platform->AddComponent<SpriteRenderer>();

	platform->GetTransform()->SetPosition(Vector3(0.0f, -1.0f, 0.0f));
	platform->GetTransform()->SetScale(Vector3(2.0f, 0.1f, 0.0f));

	platform->AddComponent<BoxCollider>();
}

void PhysicsExample::OnUpdate()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		Entity* box = m_Scene->CreateEntity();
		box->AddComponent<SpriteRenderer>();

		box->GetTransform()->SetPosition(Vector3f(0.0f, 0.5f, 0.0f));
		box->GetTransform()->SetEulerAngles(Vector3f(0.0f, 0.0f, 30.0f));
		box->GetTransform()->SetScale(Vector3f(0.3f, 0.3f, 0.0f));

		box->AddComponent<BoxCollider>();
		box->AddComponent<Rigidbody>();
	}
}