#pragma once
#include "../Component.h"

class Trigger : virtual public Component
{
protected:
	bool m_IsTrigger = false;

protected:
	Trigger(Entity* owner);

	virtual ~Trigger() = default;
};