#include "Camera.h"
#include "Transform.h"
#include "../Math/MatrixTransform.h"

void Camera::RecalculateProjectionMatrix()
{
	switch (m_ProjectionType)
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
{
	RecalculateProjectionMatrix();
}

void Camera::SetProjectionType(ProjectionType type)
{
	m_ProjectionType = type;
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

Ray Camera::GetRay(double u, double v) const
{
	//Vector3f origin = m_Transform->GetPosition();
	//return Ray(origin,  )
	return Ray();
}

Camera::ProjectionType Camera::GetProjectionType() const
{
	return m_ProjectionType;
}

float Camera::GetAspectRation() const
{
	return m_AspectRation;
}

float Camera::GetNearClip() const
{
	return m_NearClip;
}

float Camera::GetFarClip() const
{
	return m_FarClip;
}

float Camera::GetFov() const
{
	return m_Fov;
}

const Matrix4x4f& Camera::GetProjectionMatrix() const
{
	return m_ProjectionMatrix;
}

Matrix4x4f Camera::GetViewProjectionMatrix() const
{
	return m_ProjectionMatrix * m_Transform->GetTransformMatrix();
}