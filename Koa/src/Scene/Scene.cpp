#include "Scene.h"

//Remove later
#include "../Core/Engine.h"
#include "../Core/Time.h"
#include "../Physics/Physics.h"
#include "../Components/Renderers/SpriteRenderer.h"
#include "../Components/Renderers/PixelRenderer.h"
#include "../Components/Transform.h"
#include "../Math/VectorOperations.h"

Scene::Scene()
	:m_Name("None")
{ 
}

void Scene::Start()
{
	Physics::CreateWorld();
}

void Scene::Update()
{
	static double duration = 0;
	duration += Time::DeltaTime();

	std::for_each(m_Entities.begin(), m_Entities.end(),
		[](std::unique_ptr<Entity>& entity)
		{
			entity->ComponentsUpdate();
		});

	//Fixed Update 
	if (duration >= Time::FixedDeltaTime())
	{
		Physics::Update();

		for (auto it = m_Entities.begin(), end = m_Entities.end(); it != end; ++it)
		{
			if ((*it)->IsActive())
			{
				(*it)->ComponentsFixedUpdate();
			}
		}

		duration = 0;
	}
}

void Scene::Render()
{
	std::vector<Vector2f> squareVerticies =
	{ { -0.5f, -0.5f },
	  { -0.5f,  0.5f },
	  {  0.5f,  0.5f },
	  {  0.5f, -0.5f } };
	//GetComponent of RenderType
	for (size_t i = 0; i < m_Entities.size(); i++)
	{
		if (m_Entities[i]->HasComponent<SpriteRenderer>())
		{
			std::vector<Vector3f> verticies;
			for (size_t i = 0; i < squareVerticies.size(); i++)
			{
				verticies.push_back(squareVerticies[i]);
			}

			SpriteRenderer* spriteRenderer = m_Entities[i]->GetComponent<SpriteRenderer>();
			Matrix4x4f transformMatrix = m_Entities[i]->GetTransform()->GetTransformMatrix();
			for (size_t j = 0; j < verticies.size(); j++)
			{
				verticies[j] = transformMatrix * verticies[j];
				verticies[j].x += transformMatrix[0][3];
				verticies[j].y += transformMatrix[1][3];
			}

			Engine::Get().GetWindow()->DrawVerticies(verticies, spriteRenderer->GetColor());
		}
	}

	for (size_t i = 0; i < m_Entities.size(); i++)
	{
		if (m_Entities[i]->HasComponent<PixelRenderer>())
		{
			PixelRenderer* pixelRenderer = m_Entities[i]->GetComponent<PixelRenderer>();
			
			Vector3f position = pixelRenderer->GetTransform()->GetPosition();
			Engine::Get().GetWindow()->SetPixel(position.x, position.y, pixelRenderer->GetColor());
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