#include "Physics.h"
#include "../Core/Time.h"

void Physics::CreateWorld()
{
	s_World = std::make_unique<b2World>(s_Gravity);
}

void Physics::Update()
{
	s_World->Step(Time::FixedDeltaTime(), s_VelocityIterations, s_PositionIterations);
}

void Physics::DestoryWorld()
{
	s_World.reset();
}

b2Body* Physics::CreateBody(const b2BodyDef& bodyDef)
{
	return s_World->CreateBody(&bodyDef);
}

void Physics::SetGravity(const Vector2f& gravity)
{
	s_Gravity.x = gravity.x;
	s_Gravity.y = gravity.y;
}