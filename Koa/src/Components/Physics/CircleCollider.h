#pragma once
#include "box2d/b2_circle_shape.h"
#include "Collider.h"

class b2CircleShape;

class KOA CircleCollider : public Collider
{
private:
	b2CircleShape m_Shape;
	float m_Radius = 0.5f;

private:
	void SetShape() override;

public:
	CircleCollider(Entity* entity);

	void Start() override;

	void SetRadius(float radius);
	float GetRadius() const { return m_Radius; }

	//void Serialize(json& out) const override;
	//void Deserialize(json& in) override;
};