#pragma once
#include <memory>
#include "box2d/b2_world.h"
#include "../Core/Core.h"
#include "../Math/Vector2.h"

class KOA_API PhysicsWorld
{
private:
	inline static std::unique_ptr<b2World> s_PhysicsWorld;
	inline static b2Vec2 s_Gravity = b2Vec2(0.0f, -10.0f);

	inline static int32 s_VelocityIterations = 6;
	inline static int32 s_PositionIterations = 2;

	friend class Scene;
	friend class Rigidbody;
	friend class Collider;
private:
	static void CreateWorld();
	static void UpdateWorld();
	static void DestoryWorld();
	static b2Body* CreateBody(const b2BodyDef& bodyDef);
	static b2World* GetNativeWorld();

public:
	static void SetGravity(const Vector2f& gravity);

	PhysicsWorld() = delete;
	PhysicsWorld(const PhysicsWorld& other) = delete;
	PhysicsWorld& operator=(const PhysicsWorld& other) = delete;
};