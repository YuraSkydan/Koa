#include "BoxCollider.h"
#include "../Transform.h"
#include "../../Scene/Entity.h"

void BoxCollider::SetShape()
{
	Vector3f scale = m_Transform->GetScale();
	float sizeX = m_Size.x * scale.x;
	float sizeY = m_Size.y * scale.y;
	b2Vec2 center = b2Vec2(m_Offset.x, m_Offset.y);

	m_Shape.SetAsBox(abs(sizeX), abs(sizeY), center, 0);
}

BoxCollider::BoxCollider(Entity* owner)
	: Collider(owner),
	  Component(owner)
{ }

void BoxCollider::Start()
{
	m_FixtureDef.shape = &m_Shape;
	Collider::Start();
}

void BoxCollider::Reset()
{
	Collider::Reset();
	m_Size = { 0.5f, 0.5f };
}

void BoxCollider::SetSize(const Vector2f& size)
{
	m_Size = size;

	if (m_Body != nullptr)
	{
		b2Fixture* fixture = m_Body->GetFixtureList();
		m_Body->DestroyFixture(fixture);
		
		SetShape();
		m_Body->CreateFixture(&m_FixtureDef);
	}
}