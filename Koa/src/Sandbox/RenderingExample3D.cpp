#include "RenderingExample3D.h"
#include "../Core/Engine.h"
#include "../Core/Input.h"
#include "../Core/Time.h"
#include "../Components/Mesh.h"
#include "../Components/Camera.h"
#include "../Components/Transform.h"
#include "../Components/Renderers/SpriteRenderer.h"

RenderingExample3D::RenderingExample3D()
{
	m_Scene = Engine::Get().GetScene();

	Entity* camera = m_Scene->CreateEntity();
	camera->AddComponent<Camera>();

	m_Mesh = m_Scene->CreateEntity();
	Mesh* component = m_Mesh->AddComponent<Mesh>();
	component->LoadMesh("Resources/african_head.obj");

	Transform* transform = m_Mesh->GetTransform();
	transform->SetPosition(Vector3f(0, 0, 0));
	//Entity* newEntity = m_Scene->CreateEntity();
	//newEntity->AddComponent<SpriteRenderer>();
	//newEntity->AddComponent<Mesh>();
}

void RenderingExample3D::OnUpdate()
{
	Vector3f position = m_Mesh->GetTransform()->GetPosition();
	Vector3f angles = m_Mesh->GetTransform()->GetEulerAngles();

	if (Input::IsKeyPressed(Key::W))
	{
		position.z += Time::DeltaTime() * 100;
	}
	if (Input::IsKeyPressed(Key::S))
	{
		position.z -= Time::DeltaTime() * 100;
	}
	if (Input::IsKeyPressed(Key::D))
	{
		angles.y += Time::DeltaTime() * 50;
	}
	if (Input::IsKeyPressed(Key::A))
	{
		angles.y -= Time::DeltaTime() * 50;
	}

	m_Mesh->GetTransform()->SetPosition(position);
	m_Mesh->GetTransform()->SetEulerAngles(angles);
}