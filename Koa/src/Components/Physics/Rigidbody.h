#pragma once
#include "box2d/b2_body.h"
#include "../Component.h"
#include "../../Math/Vector2.h"

enum class KOA_API BodyType { Static = 0, Kinematic, Dynamic };
enum class KOA_API ForceMode { Force = 0, Acceleration, Impulse, VelocityChange };

class KOA_API Rigidbody : public Component
{
private:
	b2Body* m_Body = nullptr;
	BodyType m_Type = BodyType::Dynamic;

	float m_Mass = 1.0f;
	float m_LinearDrag = 0.0f;
	float m_AngularDrag = 0.05f;
	float m_GravityScale = 1.0f;

	bool m_FixedRotation = false;

	friend class Collider;
	friend class BoxCollider;
	friend class CircleCollider;
	friend class PolygonCollider;
private:
	void SetBody(b2Body* body);
	b2Body* GetBody() const { return m_Body; }

public:
	Rigidbody(Entity* owner);

	void Awake() override;
	void Update() override;
	void FixedUpdate() override;
	void Reset() override;

	void AddForce(const Vector2f& force, const ForceMode& mode = ForceMode::Force);
	void AddAngularImpulse(float impulse);
	void AddTorque(float torque);

	//---------------------------------------------------------
	//Setters
	void SetLinearVelocity(const Vector2f& velocity);
	void SetAngularVelocity(float velocity);
	void SetAngularDrag(float drag);
	void SetLinearDrag(float drag);
	void SetFixedRotation(bool value);
	void SetGravityScale(float scale);
	void SetBodyType(BodyType type);
	void SetMass(float mass);

	//---------------------------------------------------------
	//Getters
	Vector2f GetLinearVelocity() const;

	float GetAngularVelocity() const;
	float GetGravityScale() const;
	float GetAngularDrag() const;
	float GetLinearDrag() const;
	float GetMass() const;

	bool GetFixedRotation() const;
	BodyType GetBodyType() const;
};