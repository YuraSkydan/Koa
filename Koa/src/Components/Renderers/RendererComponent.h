#pragma once
#include "../Component.h"
#include "../../Window/Color.h"

class RendererComponent : public Component
{
protected:
	Color m_Color;

public:
	RendererComponent(Entity* owner);

	void SetColor(Color color);
	void SetShade(Color::Shade shade);

	Color& GetColor();
	Color GetColor() const;
	Color::Shade GetShade() const;
};