#pragma once
#include "box2d/b2_circle_shape.h"
#include "Collider.h"

class b2CircleShape;

class KOA_API CircleCollider : public Collider
{
private:
	b2CircleShape m_Shape;
	float m_Radius = 0.5f;

private:
	void SetShape() override;

public:
	CircleCollider(Entity* owner);

	void Start() override;

	void SetRadius(float radius);
	float GetRadius() const;
};