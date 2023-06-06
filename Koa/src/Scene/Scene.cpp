#include <array>

#include "Scene.h"

//Remove later
#include "../Core/Engine.h"
#include "../Core/Time.h"
#include "../Physics/PhysicsWorld.h"
#include "../Components/Renderers/SpriteRenderer.h"
#include "../Components/Renderers/CircleRenderer.h"
#include "../Components/Renderers/LineRenderer.h"
#include "../Components/Renderers/PixelRenderer.h"
#include "../Components/Transform.h"
#include "../Components/Camera.h"
#include "../Components/Mesh.h"
#include "../Math/VectorOperations.h"
#include "../Math/Vector4.h"
#include "../Renderer/Renderer.h"

Scene::Scene()
	:m_Name("None")
{
}

void Scene::Start()
{
	PhysicsWorld::CreateWorld();
}

void Scene::Update()
{
	static double duration = 0;
	duration += Time::DeltaTime();

	for (auto& entity : m_Entities)
	{
		if (entity->IsActive())
		{
			entity->ComponentsUpdate();
		}
	}

	//Fixed Update 
	if (duration >= Time::FixedDeltaTime())
	{
		PhysicsWorld::UpdateWorld();

		for (auto& entity : m_Entities)
		{
			if ((entity)->IsActive())
			{
				entity->ComponentsFixedUpdate();
			}
		}

		duration = 0;
	}
}

void Scene::Render()
{
	Camera* renderCamera = nullptr;
	for (const auto& entity : m_Entities)
	{
		if (entity->IsActive())
		{
			Camera* camera = entity->GetComponent<Camera>();
			if (camera != nullptr && camera->IsEnabled())
			{
				renderCamera = camera;
			}
		}
	}

	Renderer::StartRendering(renderCamera);

	//Rendering sprites
	for (const auto& renderer : m_SpriteRenderers)
	{
		const Entity* owner = renderer->GetOwner();
		if (owner->IsActive())
		{
			if (renderer->IsEnabled())
			{
				Renderer::DrawSprite(renderer);
			}
		}
	}

	//Rendering circles
	for (const auto& renderer : m_CircleRenderers)
	{
		const Entity* owner = renderer->GetOwner();
		if (owner->IsActive())
		{
			if (renderer->IsEnabled())
			{
				Renderer::DrawCircle(renderer);
			}
		}
	}

	//Rendering lines
	for (const auto& renderer : m_LineRenderers)
	{
		const Entity* owner = renderer->GetOwner();
		if (owner->IsActive())
		{
			if (renderer->IsEnabled())
			{
				Renderer::DrawLine(renderer);
			}
		}
	}

	//Rendering pixels
	for (const auto& renderer : m_PixelRenderers)
	{
		const Entity* owner = renderer->GetOwner();
		if (owner->IsActive())
		{
			if (renderer->IsEnabled())
			{
				Renderer::DrawPixel(renderer);
			}
		}
	}

	//Rendering meshes
	for (const auto& mesh : m_Meshes)
	{
		const Entity* owner = mesh->GetOwner();
		if (owner->IsActive())
		{
			if (mesh->IsEnabled())
			{
				Renderer::DrawMesh(mesh);
			}
		}
	}

	//Remove later
	for (const auto& entity : m_Entities)
	{
		const LineRenderer* renderer = entity->GetComponent<LineRenderer>();
		if (renderer != nullptr)
		{
			Renderer::DrawLine(renderer);
		}
	}
}

void Scene::Raytrace()
{

}

Entity* Scene::CreateEntity()
{
	m_Entities.push_back(std::make_unique<Entity>(this));
	return m_Entities.back().get();
}