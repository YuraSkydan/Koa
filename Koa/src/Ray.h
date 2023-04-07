#pragma once
#include "Math/Vector3.h"

class Ray
{
private:
	Vector3f m_Origin;
	Vector3f m_Direction;

public:
	Ray() = default;
	Ray(const Vector3f& origin, const Vector3f& direction);

	Vector3f At(float t) const;

	void SetOrigin(const Vector3f& origin);
	void SetDirection(const Vector3f& direction);

	const Vector3f& GetOrigin() const;
	const Vector3f& GetDirection() const;
};