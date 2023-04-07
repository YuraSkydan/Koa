#pragma once
#include "../Core/Layer.h"
#include "../Scene/Scene.h"

class RenderingExample : public Layer 
{
public:
	Scene* m_Scene;

	Entity* m_Entity;

public:
	RenderingExample();
	void OnAttach() override;
	void OnUpdate() override;
};