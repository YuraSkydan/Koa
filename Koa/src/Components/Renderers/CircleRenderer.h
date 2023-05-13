#pragma once
#include "RendererComponent.h"

class CircleRenderer : public RendererComponent
{
private:
	float m_Radius;

public:
	CircleRenderer(Entity* owner);

	void SetRadius(float radius);
	float GetRadius() const;
};

