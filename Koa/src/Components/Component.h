#pragma once
#include "../Core/Core.h"

class Entity;
class Transform;

class KOA_API Component
{
protected:
	bool m_IsEnabled = true;
	Entity* m_Owner;

public:
	Component(Entity* entity);

	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void LateUpdate() {}	
	virtual void OnEnable() {}
	virtual void OnDisable() {}
	virtual void Reset() {}

	Entity* GetOwner() const;
	Transform* GetTransform() const;

	void SetEnabled(bool enabled);
	bool IsEnabled() const;

	template<typename T>
	T* GetComponent() const;

	template<typename T>
	T* GetComponentInParent() const;

	template<typename T>
	bool HasComponent() const;

	template<typename T>
	bool HasComponentInParent() const;

	Component& operator=(const Component& other);

	virtual ~Component() = default;
	//---------------------------------------
	//Delted Methods
	Component(const Component& other) = delete;
};