#pragma once
#include "Material.h"

class Metal : public Material
{
private:
	Vector3f m_Albedo;

public:
	Metal(const Vector3f& albedo);
	virtual bool Scatter(const Ray& rIn, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const override;
};