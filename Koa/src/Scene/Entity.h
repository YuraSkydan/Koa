#pragma once
#include <vector>
#include <memory>
#include <string>

#include "../Components/Component.h"

class Scene;

class Entity
{
private:
	bool m_IsActive = true;
	std::string m_Name;

	Scene* m_Scene;
	Transform* m_Transform;
	//Tag m_Tag;

	std::vector<std::unique_ptr<Component>> m_Components;
	std::vector<std::unique_ptr<Component>> m_NewComponents;
private:
	//template<typename... Components>
	//void CopyComponents(const GameObject& gameObject)
	//{
	//	([&]()
	//		{
	//			if (gameObject.HasComponent<Components>())
	//			{
	//				Components* component = GetComponent<Components>();
	//				if (component == nullptr)
	//					component = AddComponent<Components>();

	//				*component = *(gameObject.GetComponent<Components>());
	//			}
	//		}(), ...);
	//}
	void RemoveComponent(Component* component);

	//void AddScript(Script* script);

public:
	Entity(Scene* scene);
	//Entity(Scene* scene, const Entity& other);

	void ProcessNewComponents();
	void ComponentsAwake();
	void ComponentsStart();
	void ComponentsUpdate();
	void ComponentsFixedUpdate();

	//------------------------------------------------------------
	//Setters
	//void SetLayer(const LayerMask& layer);
	//void SetName(const std::string& name);
	void SetActive(bool active);
	//void SetTag(const Tag& tag);

	//------------------------------------------------------------
	//Getters
	//const LayerMask& GetLayer() const { return m_Layer; }
	//const char* GetName() const { return m_Name; }
	//unsigned int GetID() const { return m_ID; }
	//const Tag& GetTag() const { return m_Tag; }
	Transform* GetTransform() const;
	Scene* GetScene() const;
	bool IsActive() const;

	//const std::vector<std::unique_ptr<Component>>& GetComponents() const { return m_Components; }
	//const std::vector<Script*>& GetScripts() const { return m_Scripts; }

	//------------------------------------------------------------
	//Component operations
	//Definition in Scene.h
	template<typename T>
	T* AddComponent();

	template<typename T>
	T* AddComponentToParent();

	template<typename T>
	T* GetComponent() const;

	template<typename T>
	T* GetComponentInParent() const;

	template<typename T>
	void RemoveComponent();

	template<typename T>
	void RemoveComponentInParent();

	template<typename T>
	bool HasComponent() const;

	template<typename T>
	bool HasComponentInParent() const;

	~Entity();

	//------------------------------------------------------------
	//Deleted Methods
	Entity(const Entity& other) = delete;
	const Entity& operator=(const Entity& other) = delete;
};