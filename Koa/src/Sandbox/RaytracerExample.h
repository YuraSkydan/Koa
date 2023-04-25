#pragma once
#include <vector>
#include "../Core/Layer.h"
#include "../Math/Vector3.h"

class Ray;
class Scene;
class Sphere;

class RaytracerExample : public Layer
{
private:
	Scene* m_Scene;
	std::vector<Sphere*> m_Spheres;
	Vector3f m_PlayerPosition;

	float m_CameraAngle = 0;

	int m_MaxDepth = 0;

private:
	Vector3f ColorRaytrace(const Ray& ray, int depth);
	void RaytracePart(float xStart, float xEnd);

public:
	RaytracerExample();
	void OnUpdate() override;
};