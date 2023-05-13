#include "Rigidbody.h"
#include "../Transform.h"
#include "../../Math/Math.h"
#include "../../Physics/PhysicsWorld.h"

Rigidbody::Rigidbody(Entity* owner)
	:Component(owner)
{ }

void Rigidbody::Awake()
{
	b2BodyDef bodyDef;
	Vector3f position = GetTransform()->GetPosition();
	bodyDef.position = { position.x, position.y };
	bodyDef.angle = ToRadians(-GetTransform()->GetEulerAngles().z);

	bodyDef.type = b2BodyType(m_Type);
	bodyDef.gravityScale = m_GravityScale;
	bodyDef.fixedRotation = m_FixedRotation;
	bodyDef.linearDamping = m_LinearDrag;
	bodyDef.angularDamping = m_AngularDrag;

	m_Body = PhysicsWorld::CreateBody(bodyDef);
}

void Rigidbody::Update()
{
	if (m_Body != nullptr)
	{
		/*b2Vec2 bodyPosition = m_Body->GetPosition();
		Vector3f position = GetTransform()->GetPosition();

		float bodyAngle = m_Body->GetAngle();
		float angle = GetTransform()->GetEulerAngles().z;

		if (position.x != bodyPosition.x || position.y != bodyPosition.y ||
			angle != -ToDegrees(bodyAngle))
		{
			bodyPosition = b2Vec2(position.x, position.y);

			m_Body->SetTransform(bodyPosition, ToRads(-angle));
			m_Body->SetAwake(true);
		}*/
	}
}

void Rigidbody::FixedUpdate()
{
	if (m_Body != nullptr)
	{
		b2Vec2 bodyPosition = m_Body->GetPosition();
		GetTransform()->SetPosition(Vector2f{ bodyPosition.x, bodyPosition.y });

		Vector3f newAngles = GetTransform()->GetEulerAngles();
		newAngles.z = ToDegrees(m_Body->GetAngle());
		GetTransform()->SetEulerAngles(newAngles);
	}
}

void Rigidbody::Reset()
{
	m_Type = BodyType::Dynamic;
	m_Mass = 1.0f;
	m_LinearDrag = 0.0f;
	m_AngularDrag = 0.05f;
	m_GravityScale = 1.0f;
	m_FixedRotation = false;
}

void Rigidbody::AddForce(const Vector2f& force, const ForceMode& mode)
{
	if (m_Body != nullptr)
	{
		b2Vec2 b2Force(force.x, force.y);

		switch (mode)
		{
		case ForceMode::Force:
			m_Body->ApplyForceToCenter(b2Force, true);
			break;

		case ForceMode::Impulse:
			m_Body->ApplyLinearImpulseToCenter(b2Force, true);
			break;
		}
	}
}

void Rigidbody::AddAngularImpulse(float impulse)
{
	if (m_Body != nullptr)
		m_Body->ApplyAngularImpulse(impulse, true);
}

void Rigidbody::AddTorque(float torque)
{
	if (m_Body != nullptr)
		m_Body->ApplyTorque(torque, true);
}

void Rigidbody::SetLinearVelocity(const Vector2f& velocity)
{
	if (m_Body != nullptr)
	{
		b2Vec2 b2Velocity(velocity.x, velocity.y);
		m_Body->SetLinearVelocity(b2Velocity);
	}
}

void Rigidbody::SetAngularVelocity(float velocity)
{
	if (m_Body != nullptr)
		m_Body->SetAngularVelocity(velocity);
}

void Rigidbody::SetMass(float mass)
{
	if (mass > 0)
	{
		m_Mass = mass;

		if (m_Body != nullptr)
		{
			b2MassData data = m_Body->GetMassData();
			data.mass = mass;
			m_Body->SetMassData(&data);
		}
	}
}

void Rigidbody::SetLinearDrag(float drag)
{
	if (drag >= 0)
	{
		m_LinearDrag = drag;

		if (m_Body != nullptr)
		{
			m_Body->SetLinearDamping(drag);
		}
	}
}

void Rigidbody::SetFixedRotation(bool value)
{
	m_FixedRotation = value;

	if (m_Body != nullptr)
		m_Body->SetFixedRotation(m_FixedRotation);
}

void Rigidbody::SetGravityScale(float scale)
{
	m_GravityScale = scale;

	if (m_Body != nullptr)
		m_Body->SetGravityScale(scale);
}

void Rigidbody::SetBodyType(BodyType type)
{
	m_Type = type;

	if (m_Body != nullptr)
		m_Body->SetType(b2BodyType(type));
}

void Rigidbody::SetAngularDrag(float drag)
{
	if (drag >= 0)
	{
		m_AngularDrag = drag;

		if (m_Body != nullptr)
		{
			m_Body->SetAngularDamping(drag);
		}
	}
}

Vector2f Rigidbody::GetLinearVelocity() const
{
	auto velocity = m_Body->GetLinearVelocity();
	return Vector2f(velocity.x, velocity.y);
}

void Rigidbody::SetBody(b2Body* body)
{
	m_Body = body;
}

float Rigidbody::GetAngularVelocity() const
{
	return m_Body->GetAngularVelocity();
}

float Rigidbody::GetGravityScale() const 
{
	return m_GravityScale;
}

float Rigidbody::GetAngularDrag() const
{
	return m_AngularDrag;
}

float Rigidbody::GetLinearDrag() const
{
	return m_LinearDrag;
}

float Rigidbody::GetMass() const
{
	return m_Mass;
}

bool Rigidbody::GetFixedRotation() const
{
	return m_FixedRotation;
}

BodyType Rigidbody::GetBodyType() const
{
	return m_Type;
}