#include "RenderingExample3D.h"
#include "../Core/Engine.h"
#include "../Components/Mesh.h"
#include "../Components/Camera.h"
#include "../Components/Renderers/SpriteRenderer.h"

RenderingExample3D::RenderingExample3D()
{
	m_Scene = Engine::Get().GetScene();

	Entity* camera = m_Scene->CreateEntity();
	camera->AddComponent<Camera>();

	//Entity* newEntity = m_Scene->CreateEntity();
	//newEntity->AddComponent<SpriteRenderer>();
	//newEntity->AddComponent<Mesh>();
}