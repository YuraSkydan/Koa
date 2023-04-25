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
	void SetConsoleColorShade(Color::Shade shade);

	const Color& GetColor() const;
};