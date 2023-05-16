#include "Camera.h"
#include "../Math/MatrixTransform.h"

void Camera::RecalculateProjectionMatrix()
{
	switch (m_Type)
	{
	case ProjectionType::Prespective:
		m_ProjectionMatrix = MatrixTransform::PrespectiveMatrix(m_Fov, m_AspectRation, m_NearClip, m_FarClip);
		break;
	case ProjectionType::Orthographic:
		//m_ProjectionMatrix = MatrixTransform::OrthographicMatrix(0);
		break;
	}
}

Camera::Camera(Entity* owner)
	: Component(owner)
{ }

void Camera::SetProjectionType(ProjectionType type)
{
	m_Type = type;
	RecalculateProjectionMatrix();
}

void Camera::SetRatio(float aspectRation)
{
	m_AspectRation = aspectRation;
	RecalculateProjectionMatrix();
}

void Camera::SetNearClip(float nearClip)
{
	m_NearClip = nearClip;
	RecalculateProjectionMatrix();
}

void Camera::SetFarClip(float farClip)
{
	m_FarClip = farClip;
	RecalculateProjectionMatrix();
}

float Camera::GetAspectRation() const
{
	return m_AspectRation;
}

const Matrix4x4f& Camera::GetProjectionMatrix() const
{
	return m_ProjectionMatrix;
}