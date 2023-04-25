#include "Component.h"
#include "../Scene/Entity.h"

Component::Component(Entity* owner)
	: m_Owner(owner)
{
	m_Transform = m_Owner->GetTransform();
}

Entity* Component::GetOwner() const
{
	return m_Owner;
}

Transform* Component::GetTransform() const
{
	return m_Owner->GetTransform();
}

void Component::SetEnabled(bool enabled)
{
	m_IsEnabled = enabled;
}

bool Component::IsEnabled() const
{
	return m_IsEnabled;
}

Component& Component::operator=(const Component& other)
{
	m_IsEnabled = other.m_IsEnabled;
	return *this;
}