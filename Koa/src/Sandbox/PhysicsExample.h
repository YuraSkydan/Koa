#pragma once
#include "../Core/Layer.h"
#include "../Scene/Scene.h"

class PhysicsExample : public Layer
{
private:
	Scene* m_Scene;

public:
	PhysicsExample();
	void OnUpdate() override;
};