#include "Collider.h"
#include "Rigidbody.h"
#include "../../Scene/Scene.h"
#include "../../Physics/Physics.h"
#include "../../Math/Math.h"

Collider::Collider(Entity* entity)
	: Trigger(entity)
	, Collision(entity)
	, Component(entity)
{ }

void Collider::Start()
{
	if (HasComponent<Rigidbody>())
	{
		Rigidbody* rigidbody = GetComponent<Rigidbody>();
		m_Body = rigidbody->GetBody();
	}
	else
	{
		b2BodyDef bodyDef;	
		Vector3f position = GetTransform()->GetPosition();
		float angle = GetTransform()->GetEulerAngles().z;

		bodyDef.position = { position.x, position.y};
		bodyDef.angle = ToRads(-angle);
		m_Body = Physics::CreateBody(bodyDef);
	}

	SetShape();
	SetFixtureDef();
	m_Body->CreateFixture(&m_FixtureDef);
}

void Collider::Reset()
{
	m_Offset = { 0.0f, 0.0f };
	material.dencity = 1.0f;
	material.friction = 0.4f;
	material.restitution = 0.0f;
}

void Collider::ResetShape()
{
	if (m_Body != nullptr)
	{
		b2Fixture* fixture = m_Body->GetFixtureList();
		m_Body->DestroyFixture(fixture);

		SetShape();
		m_Body->CreateFixture(&m_FixtureDef);
	}
}

void Collider::ResetFixture()
{
	if (m_Body != nullptr)
	{
		b2Fixture* fixture = m_Body->GetFixtureList();
		m_Body->DestroyFixture(fixture);

		SetFixtureDef();
		m_Body->CreateFixture(&m_FixtureDef);
	}
}

void Collider::SetOffset(const Vector2f& offset)
{
	m_Offset = offset;
	ResetShape();
}

void Collider::SetIsTrigger(bool isTrigger)
{
	m_IsTrigger = isTrigger;
	ResetFixture();
}

void Collider::SetFixtureDef()
{
	m_FixtureDef.density = material.dencity;
	m_FixtureDef.restitution = material.restitution;
	m_FixtureDef.friction = material.friction;
	m_FixtureDef.isSensor = m_IsTrigger;
	//m_FixtureDef.userData.pointer = m_Entity->GetID();
}

b2Body* Collider::GetBody() const
{
	return m_Body;
}