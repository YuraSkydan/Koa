#include "RendererComponent.h"

RendererComponent::RendererComponent(Entity* owner)
    : Component(owner)
{ }

void RendererComponent::SetColor(Color color)
{
    m_Color = color;
}

void RendererComponent::SetConsoleColorShade(Color::Shade shade)
{
    m_Color.SetConsoleColorShade(shade);
}

const Color& RendererComponent::GetColor() const
{
    return m_Color;
}