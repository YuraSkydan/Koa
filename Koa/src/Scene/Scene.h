#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Entity.h"

#include "../Components/Mesh.h"

class SpriteRenderer;
class CircleRenderer;
class LineRenderer;
class PixelRenderer;
//class Mesh;

class Scene
{	
private:
	std::string m_Name;
	std::vector<std::unique_ptr<Entity>> m_Entities;

	//Render components
	std::vector<const SpriteRenderer*> m_SpriteRenderers;
	std::vector<const CircleRenderer*> m_CircleRenderers;
	std::vector<const LineRenderer*> m_LineRenderers;
	std::vector<const PixelRenderer*> m_PixelRenderers;
	std::vector<const Mesh*> m_Meshes;

public:
	Scene();

	void Start();
	void Stop();
	void Update();
	void Render();
	void Raytrace();

	Entity* CreateEntity();

	const std::string& GetName() const;

	template<typename T>
	void OnComponentAdded(const T* component);

	template<typename T>
	void OnComponentRemoved(const T* component);
};

//----------------------------------
//Component

template<typename T>
T* Component::GetComponent() const
{
	return m_Owner->GetComponent<T>();
}

template<typename T>
T* Component::GetComponentInParent() const
{
	return m_Owner->GetComponentInParent<T>();
}

template<typename T>
bool Component::HasComponent() const
{
	return m_Owner->HasComponent<T>();
}

template<typename T>
bool Component::HasComponentInParent() const
{
	return m_Owner->HasComponentInParent<T>();
}

//----------------------------------
//Entity

template<typename T>
T* Entity::AddComponent()
{
	T* returnComponent = nullptr;

	if (std::is_base_of<Component, T>::value)
	{
		auto newComponent = std::make_unique<T>(this);
		returnComponent = newComponent.get();
		m_NewComponents.push_back(std::move(newComponent));
	}

	if (returnComponent != nullptr)
	{
		m_Scene->OnComponentAdded<T>(returnComponent);
	}

	return returnComponent;
}

template<typename T>
T* Entity::AddComponentToParent()
{
	//return m_Transform->GetParent()->AddComponent<T>();
	return nullptr;
}

template<typename T>
T* Entity::GetComponent() const
{
	for (auto it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		if (T* component = dynamic_cast<T*>(it->get()))
		{
			return component;
		}
	}

	for (auto it = m_NewComponents.begin(); it != m_NewComponents.end(); ++it)
	{
		if (T* component = dynamic_cast<T*>(it->get()))
		{
			return component;
		}
	}

	return nullptr;
}

template<typename T>
T* Entity::GetComponentInParent() const
{

}

template<typename T>
void Entity::RemoveComponent()
{

}

template<typename T>
void Entity::RemoveComponentInParent()
{

}

template<typename T>
bool Entity::HasComponent() const
{
	for (auto it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		if (dynamic_cast<T*>(it->get()))
		{
			return true;
		}
	}

	for (auto it = m_NewComponents.begin(); it != m_NewComponents.end(); ++it)
	{
		if (dynamic_cast<T*>(it->get()))
		{
			return true;
		}
	}

	return false;
}

template<typename T>
bool Entity::HasComponentInParent() const
{

}

//----------------------------------
//Scene

template<typename T>
void Scene::OnComponentAdded(const T* component)
{
	if (std::is_same<T, Mesh>::value)
	{
		m_Meshes.push_back((const Mesh*)component);
	}
	else if (std::is_same<T, SpriteRenderer>::value)
	{
		m_SpriteRenderers.push_back((const SpriteRenderer*)component);
	}
}