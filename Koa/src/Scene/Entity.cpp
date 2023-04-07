#include <algorithm>
#include <iterator>

#include "Entity.h"
#include "../Components/Transform.h"

Entity::Entity(Scene* scene)
	: m_Scene(scene)
{
	m_Name = "GameObject";

	std::unique_ptr<Transform> transform = std::make_unique<Transform>(this);
	m_Transform = transform.get();
	m_Components.push_back(std::move(transform));
}

void Entity::ProcessNewComponents()
{
	if (!m_NewComponents.empty())
	{
		std::for_each(m_NewComponents.begin(), m_NewComponents.end(),
			[](std::unique_ptr<Component>& component)
			{
				component->Awake();
			});

		std::for_each(m_NewComponents.begin(), m_NewComponents.end(),
			[](std::unique_ptr<Component>& component)
			{
				component->Start();
			});

		std::move(std::begin(m_NewComponents), std::end(m_NewComponents), std::back_inserter(m_Components));

		m_NewComponents.clear();
	}
}

void Entity::ComponentsAwake()
{
	//Problems may occure if Awake Methods deletes components
	/*for (auto it = m_Components.begin(), end = m_Components.end(); it != end; ++it)
	{
		(*it)->Awake();
	}*/
}

void Entity::ComponentsStart()
{
	/*for (auto it = m_Components.begin(), end = m_Components.end(); it != end; ++it)
	{
		(*it)->Start();
	}*/
}

void Entity::ComponentsUpdate()
{
	ProcessNewComponents();

	for (auto it = m_Components.begin(), end = m_Components.end(); it != end; ++it)
	{
		(*it)->Update();
	}
}

void Entity::ComponentsFixedUpdate()
{
	for (auto it = m_Components.begin(), end = m_Components.end(); it != end; ++it)
	{
		(*it)->FixedUpdate();
	}
}

void Entity::SetActive(bool active)
{
	m_IsActive = active;
}

Transform* Entity::GetTransform() const
{
	return m_Transform;
}

Scene* Entity::GetScene() const
{
	return m_Scene;
}

bool Entity::IsActive() const
{
	return m_IsActive;
}

Entity::~Entity()
{

}