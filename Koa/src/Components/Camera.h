#pragma once
#include "Component.h"
#include "../Math/Matrix.h"
#include "../Raytracing/Ray.h"
//#include "../Scene/LayerMask.h"
//#include "SpriteRenderer.h"

class KOA_API Camera : public Component
{
public:
	enum class ProjectionType { Prespective = 0, Orthographic = 1 };

private:
	ProjectionType m_ProjectionType = ProjectionType::Prespective;
	float m_AspectRation = 1.0f;
	float m_NearClip = 0.1f;
	float m_FarClip = 100.0f;
	float m_Fov = 90.0f;
	Matrix4x4f m_ProjectionMatrix;
	//Color backgroundColor;
	//LayerMask cullingMask;

private:
	void RecalculateProjectionMatrix();

public:
	Camera(Entity* owner);

	void SetProjectionType(ProjectionType type);
	void SetRatio(float aspectRation);
	void SetNearClip(float nearClip);
	void SetFarClip(float farClip);
	
	Ray GetRay(double u, double v) const;
	ProjectionType GetProjectionType() const;
	float GetAspectRation() const;
	float GetNearClip() const;
	float GetFarClip() const;
	float GetFov() const;

	const Matrix4x4f& GetProjectionMatrix() const;
	Matrix4x4f GetViewProjectionMatrix() const;
};