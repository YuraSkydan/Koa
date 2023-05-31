#pragma once
#include <numbers>
#include <cmath>

#include "Matrix.h"
#include "Vector2.h"

namespace MatrixTransform
{
	template<typename T>
	Matrix<T, 2> Rotate(const Matrix<T, 2>& m, float angle)
	{
		Matrix<T, 2> rotated = m;

		float cosValue = cos(angle * (std::numbers::pi / 180.0f));
		float sinValue = sin(angle * (std::numbers::pi / 180.0f));
	
		rotated[0][0] = m[0][0] * cosValue - m[1][0] * sinValue;
		rotated[0][1] = m[0][1] * cosValue - m[1][1] * sinValue;

		rotated[1][0] = m[0][0] * sinValue + m[1][0] * cosValue;
		rotated[1][1] = m[0][1] * sinValue + m[1][1] * cosValue;

		return rotated;
	}
	
	template<typename T>
	Matrix<T, 2> Scale(const Matrix<T, 2>& m, const Vector2<T>& v)
	{
		Matrix<T, 3> scaled = m;

		scaled[0][0] = m[0][0] * v.x;
		scaled[0][1] = m[0][1] * v.x;

		scaled[1][0] = m[1][0] * v.y;
		scaled[1][1] = m[1][1] * v.y;

		return scaled;
	}

	template<typename T>
	Matrix<T, 3> Translate(const Matrix<T, 3>& m, const Vector2<T>& v)
	{
		Matrix<T, 3> translated = m;
		
		translated[0][2] = m[0][0] * v.x + m[0][1] * v.y + m[0][2];
		translated[1][2] = m[1][0] * v.x + m[1][1] * v.y + m[1][2];
		
		return translated;
	}

	template<typename T>
	Matrix<T, 3> Rotate(const Matrix<T, 3>& m, float angle)
	{
		Matrix<T, 3> rotated = m;

		float cosValue = cos(angle * (std::numbers::pi / 180.0f));
		float sinValue = sin(angle * (std::numbers::pi / 180.0f));

		rotated[0][0] = m[0][0] * cosValue - m[1][0] * sinValue;
		rotated[0][1] = m[0][1] * cosValue - m[1][1] * sinValue;

		rotated[1][0] = m[0][0] * sinValue + m[1][0] * cosValue;
		rotated[1][1] = m[0][1] * sinValue + m[1][1] * cosValue;

		return rotated;
	}

	template<typename T>
	Matrix<T, 3> Rotate(const Matrix<T, 3>& m, const Vector3<T>& v)
	{
		return Matrix<T, 3>();
	}

	template<typename T>
	Matrix<T, 3> Scale(const Matrix<T, 3>& m, const Vector2<T> v)
	{
		Matrix<T, 3> scaled = m;

		scaled[0][0] = m[0][0] * v.x;
		scaled[0][1] = m[0][1] * v.x;

		scaled[1][0] = m[1][0] * v.y;
		scaled[1][1] = m[1][1] * v.y;

		return scaled;
	}

	template<typename T>
	Matrix<T, 4> Translate(const Matrix<T, 4>& m, const Vector3<T>& v)
	{
		Matrix<T, 4> translated = m;
		
		translated[0][3] = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3];
		translated[1][3] = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3];
		translated[2][3] = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3];

		return translated;
	}

	template<typename T>
	Matrix<T, 4> Rotate(const Matrix<T, 4>& m, const Vector3<T>& v)
	{
		Matrix<T, 4> rotated = m;

		float cosValue = cos(v.y * (std::numbers::pi / 180.0f));
		float sinValue = sin(v.y * (std::numbers::pi / 180.0f));

		rotated[0][0] = m[0][0] * cosValue - m[1][0] * sinValue;
		rotated[0][1] = m[0][1] * cosValue - m[1][1] * sinValue;

		rotated[1][0] = m[0][0] * sinValue + m[1][0] * cosValue;
		rotated[1][1] = m[0][1] * sinValue + m[1][1] * cosValue;


		/*rotated[1][1] = m[1][1] * cosValue - m[2][1] * sinValue;
		rotated[1][2] = m[1][2] * cosValue - m[2][2] * sinValue;

		rotated[2][1] = m[1][1] * sinValue + m[2][1] * cosValue;
		rotated[2][2] = m[1][2] * sinValue + m[2][2] * cosValue;*/

		return rotated;
	}

	template<typename T>
	Matrix<T, 4> Scale(const Matrix<T, 4>& m, const Vector3<T> v)
	{
		Matrix<T, 4> scaled = m;

		scaled[0][0] = m[0][0] * v.x;
		scaled[0][1] = m[0][1] * v.x;
		scaled[0][2] = m[0][2] * v.x;

		scaled[1][0] = m[1][0] * v.y;
		scaled[1][1] = m[1][1] * v.y;
		scaled[1][2] = m[1][2] * v.y;
								 
		scaled[2][0] = m[2][0] * v.z;
		scaled[2][1] = m[2][1] * v.z;
		scaled[2][2] = m[2][2] * v.z;

		return scaled;
	}

	Matrix4x4f PrespectiveMatrix(float fov, float aspectRatio, float nearClip, float farClip);

	Matrix4x4f OrthographicMatrix(float left, float right, float bottom, float top);
}