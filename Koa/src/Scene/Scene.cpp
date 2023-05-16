#include "Scene.h"

//Remove later
#include "../Core/Engine.h"
#include "../Core/Time.h"
#include "../Physics/PhysicsWorld.h"
#include "../Components/Renderers/SpriteRenderer.h"
#include "../Components/Renderers/PixelRenderer.h"
#include "../Components/Transform.h"
#include "../Components/Camera.h"
#include "../Math/VectorOperations.h"

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
	std::vector<Vector2f> square
	{
		{ -0.5f, -0.5f },
		{ -0.5f,  0.5f },
		{  0.5f, -0.5f },

		{  0.5f, -0.5f },
		{  0.5f,  0.5f },
		{ -0.5f,  0.5f }
	};

	//GetComponent of RenderType
	for (size_t i = 0; i < m_Entities.size(); i++)
	{
		if (m_Entities[i]->HasComponent<SpriteRenderer>())
		{
			std::vector<Vector2f> verticies(square);

			SpriteRenderer* spriteRenderer = m_Entities[i]->GetComponent<SpriteRenderer>();
			Matrix4x4f transformMatrix = m_Entities[i]->GetTransform()->GetTransformMatrix();
			for (size_t j = 0; j < verticies.size(); j++)
			{
				verticies[j] = transformMatrix * Vector3f(verticies[j]);
				verticies[j].x += transformMatrix[0][3];
				verticies[j].y += transformMatrix[1][3];
			}

			Engine::Get().GetWindow()->DrawVerticies(std::vector<Vector2f>(verticies.begin(), verticies.begin() + 3), spriteRenderer->GetColor());
			Engine::Get().GetWindow()->DrawVerticies(std::vector<Vector2f>(verticies.begin() + 3, verticies.end()), spriteRenderer->GetColor());
		}
	}

	for (size_t i = 0; i < m_Entities.size(); i++)
	{
		if (m_Entities[i]->HasComponent<PixelRenderer>())
		{
			PixelRenderer* pixelRenderer = m_Entities[i]->GetComponent<PixelRenderer>();

			Vector3f position = pixelRenderer->GetTransform()->GetPosition();
			Engine::Get().GetWindow()->SetPixel(int(position.x), int(position.y), pixelRenderer->GetColor());
		}
	}

	Camera* camera = nullptr;
	for (const auto& entity : m_Entities)
	{
		if (entity->HasComponent<Camera>())
		{
			camera = entity->GetComponent<Camera>();
		}
	}

	std::vector<Vector3f> sprite
	{
		{ 0.5f,  0.5f, 1.0f },
		{ 0.5f, -0.5f, 1.0f },
		{ -0.5f, 0.5f, 1.0f }
	};

	if (camera != nullptr)
	{
		for (auto& vertex : sprite)
		{
			//vertex = vertex * camera->GetProjectionMatrix();
		}
		//Engine::Get().GetWindow()->DrawVerticies(std > )
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