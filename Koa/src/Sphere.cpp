#include <stdexcept>

#include "Sphere.h"
#include "HitRecord.h"
#include "Components/Transform.h"
#include "Math/VectorOperations.h"

Sphere::Sphere(Entity* owner)
	: Component(owner), m_Radius(1)
{ }

bool Sphere::Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const
{
	Vector3f oc = ray.GetOrigin() - GetTransform()->GetPosition();
	Vector3f direction = ray.GetDirection();
	float a = direction.SquaredMagnitude();
	float b = Dot(direction, oc);
	float c = oc.SquaredMagnitude() - m_Radius * m_Radius;
	float discriminant = b * b - a * c;

	if (discriminant < 0)
	{
		return false;
	}

	float sqrtd = sqrt(discriminant);

	float t = 0;
	float t1 = (-b - sqrtd) / a;
	float t2 = (-b - sqrtd) / a;

	if (t1 < tMin || t1 > tMax)
	{
		if (t2 < tMin || t2 > tMax)
		{
			return false;
		}

		t = t2;
	}

	if (t2 > tMin && t2 < tMax)
	{
		if (t2 < t1)
		{
			t = t2;
		}
		else
		{
			t = t1;
		}
	}

	record.t = t;
	record.hitPoint = ray.At(record.t);
	Vector3f outwardNormal = (record.hitPoint - GetTransform()->GetPosition()) / m_Radius;
	record.SetFaceNormal(ray, outwardNormal);
	record.materialPtr = m_Material.get();

	return true;
}

void Sphere::SetMaterial(std::unique_ptr<Material> material)
{
	m_Material = std::move(material);
}

void Sphere::SetRadius(float radius)
{
	if (radius <= 0)
	{
		throw std::invalid_argument("Radius cannot be less or equal than zero.");
		return;
	}

	m_Radius = radius;
}

float Sphere::GetRadius() const
{
	return m_Radius;
}