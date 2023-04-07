#pragma once
#include "../Component.h"

class Collision : virtual public Component
{
protected:
	Collision(Entity* entity);
	virtual ~Collision() = default;
};