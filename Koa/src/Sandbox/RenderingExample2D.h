#pragma once
#include "../Core/Layer.h"
#include "../Scene/Scene.h"

class RenderingExample2D : public Layer 
{
public:
	Scene* m_Scene;

	Entity* m_Entity;

public:
	RenderingExample2D();
	void OnAttach() override;
	void OnUpdate() override;
};