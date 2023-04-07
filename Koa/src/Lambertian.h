#pragma once
#include "Material.h"

class Lambertian : public Material
{
private:
	Vector3f m_Albedo;

public:
	Lambertian(const Vector3f& albedo);
	bool Scatter(const Ray& rIn, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const override;
};