#pragma once
#include <vector>
#include "../Core/Layer.h"
#include "../Physics/PixelPhysicsGrid.h"

class Scene;
class Entity;

class PixelPhysicsExample : public Layer
{
private:
	Scene* m_Scene;
	PixelPhysicsGrid m_Grid;

public:
	PixelPhysicsExample();

	void OnUpdate() override;
};