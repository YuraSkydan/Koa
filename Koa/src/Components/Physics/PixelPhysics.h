#pragma once
#include "../Component.h"
#include "../../Math/Vector2.h"

class PixelPhysicsGrid;


class PixelPhysics : public Component
{
public:
	enum class ObjectType { Sand, Water, Fire };

	Vector2f velocity;
	ObjectType type = ObjectType::Sand;

public:
	PixelPhysics(Entity* owner);

	void Update() override;
};