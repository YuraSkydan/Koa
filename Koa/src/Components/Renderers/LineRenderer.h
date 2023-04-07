#pragma once
#include "RendererComponent.h"

class LineRenderer : public RendererComponent
{
private: 
	float m_Length = 0;

public:
	LineRenderer(Entity* owner);

	void SetLength(float length);
	float GetLength() const;
};