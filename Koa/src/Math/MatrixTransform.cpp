#include "MatrixTransform.h"
#include "Math.h"

Matrix4x4f MatrixTransform::PrespectiveMatrix(float fov, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4f prespective;

	float tanHalfFOV = std::tan(ToRadians(fov / 2.0f));
	float range = farClip - nearClip;

	prespective[0][0] = 1.0f / (aspectRatio * tanHalfFOV);
	prespective[1][1] = 1.0f / tanHalfFOV;
	prespective[2][2] = -(farClip + nearClip) / range;
	prespective[2][3] = -(2.0f * farClip * nearClip) / range;
	prespective[3][2] = -1.0f;

	return prespective;
}

Matrix4x4f MatrixTransform::OrthographicMatrix(float left, float right, float bottom, float top)
{
	Matrix4x4f orthographic;

	orthographic[0][0] = 2.0f / (right - left);
	orthographic[0][2] = -(right + left) / (right - left);
	
	orthographic[1][1] = 2.0f / (top - bottom);
	orthographic[1][2] = -(top + bottom) / (top - bottom);

	orthographic[2][2] = 1.0f;

	return orthographic;
}