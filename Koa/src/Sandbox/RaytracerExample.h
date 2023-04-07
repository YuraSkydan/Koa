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

	int m_MaxDepth = 1;

private:
	Vector3f Color(const Ray& ray, int depth);

public:
	RaytracerExample();
	void OnUpdate() override;
};