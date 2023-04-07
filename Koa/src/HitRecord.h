#pragma once
#include "Ray.h"

class Material;

struct HitRecord
{
	float t;
	Vector3f normal;
	Vector3f hitPoint;
	bool frontFace;

	Material* materialPtr;

	void SetFaceNormal(const Ray& ray, const Vector3f& outwardNormal);
};