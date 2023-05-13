#include "CircleRenderer.h"

CircleRenderer::CircleRenderer(Entity* owner)
	:RendererComponent(owner)
{ }

void CircleRenderer::SetRadius(float radius)
{
	if (radius < 0)
	{
		return;
	}

	m_Radius = radius;
}

float CircleRenderer::GetRadius() const
{
	return m_Radius;
}