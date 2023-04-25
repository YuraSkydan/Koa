#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Math.h"

template<typename T>
template<typename U>
inline Vector2<T>::Vector2(const Vector3<U>& other)
{
	x = other.x;
	y = other.y;
}

template<typename T>
template<typename U>
inline Vector3<T>::Vector3(const Vector2<U>& other)
{
	x = other.x;
	y = other.y;
}

template<typename T>
template<typename U>
Vector2<T>& Vector2<T>::operator=(const Vector3<U>& v)
{
	x = v.x;
	y = v.y;

	return *this;
}

template<typename T>
template<typename U>
Vector3<T>& Vector3<T>::operator=(const Vector2<U>& v)
{
	x = v.x;
	y = v.y;

	return *this;
}

template<typename T>
float Dot(const Vector2<T>& v1, const Vector2<T>& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

template<typename T>
float Dot(const Vector3<T>& v1, const Vector3<T>& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template<typename T>
float Cross(const Vector2<T>& v)
{
	Vector2<T> result;
	result.x = v.y;
	result.y = -v.x;

	return result;
}

template<typename T>
Vector3<T> Cross(const Vector3<T>& v1, const Vector3<T>& v2)
{
	float i = v1.y * v2.z - v1.z * v2.y;
	float j = v1.z * v2.x - v1.x * v2.z;
	float k = v1.x * v2.y - v1.y * v2.x;

	return Vector3<T>(i, j, k);
}

template<typename T>
Vector2<T> Reflect(const Vector2<T>& v, const Vector2<T>& n)
{
	return v - 2 * Dot(v, n) * n;
}

template<typename T>
Vector3<T> Reflect(const Vector3<T>& v, const Vector3<T>& n)
{
	return v - 2 * Dot(v, n) * n;
}

template<typename T>
Vector2<T> Abs(const Vector2<T>& v)
{
	return Vector2<T>(abs(v.x), abs(v.y));
}

template<typename T>
Vector3<T> Abs(const Vector3<T>& v)
{
	return Vector3<T>(abs(v.x), abs(v.y), abs(v.z));
}

Vector3f RandomInUnitSphere();