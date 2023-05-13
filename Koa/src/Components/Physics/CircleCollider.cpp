#include "CircleCollider.h"

void CircleCollider::SetShape()
{
	b2Vec2 center = b2Vec2(m_Offset.x, m_Offset.y);
	m_Shape.m_radius = m_Radius;
	m_Shape.m_p = center;
}

CircleCollider::CircleCollider(Entity* owner)
	: Collider(owner)
	, Component(owner)
{ }

void CircleCollider::Start()
{
	m_FixtureDef.shape = &m_Shape;
	Collider::Start();
}

void CircleCollider::SetRadius(float radius)
{
	m_Radius = radius;
	ResetShape();
}

float CircleCollider::GetRadius() const
{
	return m_Radius;
}