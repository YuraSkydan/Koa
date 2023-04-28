#pragma once
#include "../Math/Vector3.h"

class Ray;
struct HitRecord;

class Material
{
public:
	virtual bool Scatter(const Ray& rIn, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const = 0;
};