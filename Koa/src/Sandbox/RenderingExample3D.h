#pragma once
#include "../Scene/Scene.h"
#include "../Core/Layer.h"

class RenderingExample3D : public Layer
{
private:
	Scene* m_Scene;
	Entity* m_Mesh;

public:
	RenderingExample3D();

	void OnUpdate();
};