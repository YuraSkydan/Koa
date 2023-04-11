#include "Physics.h"
#include "../Core/Time.h"

void PhysicsWorld::CreateWorld()
{
	s_PhysicsWorld = std::make_unique<b2World>(s_Gravity);
}

void PhysicsWorld::UpdateWorld()
{
	s_PhysicsWorld->Step(Time::FixedDeltaTime(), s_VelocityIterations, s_PositionIterations);
}

void PhysicsWorld::DestoryWorld()
{
	s_PhysicsWorld.reset();
}

b2Body* PhysicsWorld::CreateBody(const b2BodyDef& bodyDef)
{
	return s_PhysicsWorld->CreateBody(&bodyDef);
}

b2World* PhysicsWorld::GetNativeWorld()
{
	return s_PhysicsWorld.get(); 
}

void PhysicsWorld::SetGravity(const Vector2f& gravity)
{
	s_Gravity.x = gravity.x;
	s_Gravity.y = gravity.y;
}