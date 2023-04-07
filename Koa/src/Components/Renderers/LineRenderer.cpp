#include "LineRenderer.h"

LineRenderer::LineRenderer(Entity* owner)
	: RendererComponent(owner)
{ }

void LineRenderer::SetLength(float length)
{
	m_Length = length;
}

float LineRenderer::GetLength() const
{
	return m_Length;
}