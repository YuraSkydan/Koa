#include "HitRecord.h"
#include "../Math/VectorOperations.h"

void HitRecord::SetFaceNormal(const Ray& ray, const Vector3f& outwardNormal)
{
	frontFace = Dot(ray.GetDirection(), outwardNormal) < 0;
	normal = frontFace ? outwardNormal : -outwardNormal;
}