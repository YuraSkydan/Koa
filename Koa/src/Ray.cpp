#include "Ray.h"

Ray::Ray(const Vector3f& origin, const Vector3f& direction)
	: m_Origin(origin), m_Direction(direction)
{ }

Vector3f Ray::At(float t) const
{
	return m_Origin + m_Direction * t;
}

void Ray::SetOrigin(const Vector3f& origin)
{
	m_Origin = origin;
}

void Ray::SetDirection(const Vector3f& direction)
{
	m_Direction = direction;
}

const Vector3f& Ray::GetOrigin() const
{
	return m_Origin;
}

const Vector3f& Ray::GetDirection() const
{
	return m_Direction;
}