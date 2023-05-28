#pragma once
#include "Collision.h"
#include "Trigger.h"
#include "PhysicsMaterial.h"
#include "box2d/b2_fixture.h"
#include "../../Math/Vector2.h"

class KOA_API Collider : public Collision, public Trigger
{
protected:
	b2Body* m_Body = nullptr;
	b2FixtureDef m_FixtureDef;
	b2Fixture* m_Fixture;
	Vector2f m_Offset{ 0.0f, 0.0f };

public: 
	PhysicsMaterial material;

protected:
	Collider(Entity* owner);

	void Start() override;

	void Reset() override;
	void ResetShape();
	void ResetFixture();
	void SetFixtureDef();
	virtual void SetShape() { };

	b2Body* GetBody() const;

public:
	void SetOffset(const Vector2f& offset);
	void SetIsTrigger(bool isTrigger);
	bool IsTrigger() const;
	const Vector2f& GetOffset() const;
};