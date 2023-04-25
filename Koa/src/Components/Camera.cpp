#include "Camera.h"

Camera::Camera(Entity* owner)
	: Component(owner)
{ }

void Camera::SetRatio(float aspectRation)
{
	m_AspectRation = aspectRation;
}

float Camera::GetAspectRation() const
{
	return m_AspectRation;
}

//Matrix3x3f Camera::GetCameraMatrix() const
//{
//	Matrix3x3f cameraMatrix(1.0f);
//
//	cameraMatrix = MatrixTransform::Rotate(cameraMatrix, -transform->angle);
//	cameraMatrix = MatrixTransform::Scale(cameraMatrix, Vector2f(m_AspectRation, 1.0f) * (1.0f / size));
//	cameraMatrix = MatrixTransform::Translate(cameraMatrix, -transform->position);
//
//	return cameraMatrix;
//}