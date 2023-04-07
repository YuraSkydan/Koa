#include "RendererComponent.h"

RendererComponent::RendererComponent(Entity* owner)
    : Component(owner)
{ }


void RendererComponent::SetColor(Color color)
{
    m_Color = color;
}

void RendererComponent::SetShade(Color::Shade shade)
{
    m_Color.SetShade(shade);
}

Color& RendererComponent::GetColor()
{
    return m_Color;
}

Color RendererComponent::GetColor() const
{
    return m_Color;
}

Color::Shade RendererComponent::GetShade() const
{
    return m_Color.GetShade();
}