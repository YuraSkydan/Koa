#pragma once
#include "Component.h"
#include "../Math/Matrix.h"
//#include "../Scene/LayerMask.h"
//#include "SpriteRenderer.h"

class KOA_API Camera : public Component
{
public:
	enum class ProjectionType { Prespective = 0, Orthographic = 1 };

private:
	ProjectionType m_Type = ProjectionType::Prespective;
	float m_AspectRation = 1.0f;
	float m_NearClip = 0.01f;
	float m_FarClip = 1000.0f;
	float m_Fov = 45.0f;
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
	float GetAspectRation() const;
	
	const Matrix4x4f& GetProjectionMatrix() const;
};