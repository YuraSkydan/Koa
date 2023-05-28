#pragma once
#include "Collider.h"
#include "box2d/b2_polygon_shape.h"

class KOA_API BoxCollider : public Collider
{
private:
	b2PolygonShape m_Shape;
	Vector2f m_Size = { 0.5f, 0.5f };

private:
	void SetShape() override;

public:
	BoxCollider(Entity* owner);

	void Start() override;
	void Reset() override;

	void SetSize(const Vector2f& size);
	const Vector2f& GetSize() const;
};