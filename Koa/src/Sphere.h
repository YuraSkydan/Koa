#pragma once
#include <memory>

#include "Components/Component.h"
#include "Material.h"

class Ray;
class HitRecord;

class Sphere : public Component
{
private:
	float m_Radius;
	std::unique_ptr<Material> m_Material;

public:
	Sphere(Entity* owner);

	bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const;
	void SetMaterial(std::unique_ptr<Material> material);
	void SetRadius(float radius);
	float GetRadius() const;
};