#include "Lambertian.h"
#include "HitRecord.h"
#include "Math/VectorOperations.h"

Lambertian::Lambertian(const Vector3f& albedo)
	: m_Albedo(albedo)
{ }

bool Lambertian::Scatter(const Ray& rIn, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const
{
	Vector3f target = record.hitPoint + record.normal + RandomInUnitSphere();
	scattered = Ray(record.hitPoint, target - record.hitPoint);
	attenuation = m_Albedo;

	return true;
}