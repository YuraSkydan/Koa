#include "Metal.h"
#include "Ray.h"
#include "HitRecord.h"
#include "../Math/VectorOperations.h"

Metal::Metal(const Vector3f& albedo)
	: m_Albedo(albedo)
{ }

bool Metal::Scatter(const Ray& rIn, const HitRecord& record, Vector3f& attenuation, Ray& scattered) const 
{
	Vector3f reflected = Reflect(rIn.GetDirection().Normalized(), record.normal);
	scattered = Ray(record.hitPoint, reflected);
	attenuation = m_Albedo;

	return (Dot(scattered.GetDirection(), record.normal) > 0);
}