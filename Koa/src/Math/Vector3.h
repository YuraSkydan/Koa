#pragma once
#include <cmath>

template<typename T>
struct Vector2;

template<typename T>
struct Vector3
{
	static Vector3<float> Zero; 
	static Vector3<float> Right;
	static Vector3<float> Left;
	static Vector3<float> Up;
	static Vector3<float> Down;
	static Vector3<float> Forward;
	static Vector3<float> Backward;

	T x, y, z;

	Vector3();
	Vector3(T value);
	Vector3(T x, T y, T z);

	template<typename U>
	Vector3(const Vector3<U>& other);

	template<typename U>
	Vector3(const Vector2<U>& other, T z);

	template<typename U>
	Vector3<T>& operator=(const Vector3<U>& v);

	template<typename U>
	Vector3<T>& operator+=(const Vector3<U>& v);

	template<typename U>
	Vector3<T>& operator-=(const Vector3<U>& v);

	template<typename U>
	Vector3<T>& operator*=(const Vector3<U>& v);

	template<typename U>
	Vector3<T>& operator/=(const Vector3<U>& v);

	template<typename U>
	Vector3<T>& operator=(U value);

	template<typename U>
	Vector3<T>& operator+=(U value);

	template<typename U>
	Vector3<T>& operator-=(U value);

	template<typename U>
	Vector3<T>& operator*=(U value);

	template<typename U>
	Vector3<T>& operator/=(U value);

	T& operator[](size_t index);

	void Normalize();
	Vector3<T> Normalized() const;
	float SquaredMagnitude() const;
	float Magnitude() const;
};

#pragma region Vectors
Vector3<float> Vector3<float>::Zero(0.0f, 0.0f, 0.0f);
Vector3<float> Vector3<float>::Right(1.0f, 0.0f, 0.0f);
Vector3<float> Vector3<float>::Left(-1.0f, 0.0f, 0.0f);
Vector3<float> Vector3<float>::Up(0.0f, 1.0f, 0.0f);
Vector3<float> Vector3<float>::Down(0.0f, -1.0f, 0.0f);
Vector3<float> Vector3<float>::Forward(0.0f, 0.0f, 1.0f);
Vector3<float> Vector3<float>::Backward(0.0f, 0.0f, -1.0f);
#pragma endregion

#pragma region Methods
template<typename T>
inline Vector3<T>::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

template<typename T>
inline Vector3<T>::Vector3(T value)
{
	x = value;
	y = value;
	z = value;
}

template<typename T>
inline Vector3<T>::Vector3(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template<typename T>
template<typename U>
inline Vector3<T>::Vector3(const Vector3<U>& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

template<typename T>
template<typename U>
inline Vector3<T>& Vector3<T>::operator=(const Vector3<U>& v)
{
	x = v.x;
	y = v.y;
	z = v.z;

	return *this;
}

template<typename T>
template<typename U>
inline Vector3<T>& Vector3<T>::operator+=(const Vector3<U>& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

template<typename T>
template<typename U>
inline Vector3<T>& Vector3<T>::operator-=(const Vector3<U>& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

template<typename T>
template<typename U>
inline Vector3<T>& Vector3<T>::operator*=(const Vector3<U>& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;

	return *this;
}

template<typename T>
template<typename U>
inline Vector3<T>& Vector3<T>::operator/=(const Vector3<U>& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;

	return *this;
}

template<typename T>
template<typename U>
inline Vector3<T>& Vector3<T>::operator=(U value)
{
	x = value;
	y = value;
	z = value;

	return *this;
}

template<typename T>
template<typename U>
inline Vector3<T>& Vector3<T>::operator+=(U value)
{
	x += value;
	y += value;
	z += value;

	return *this;
}

template<typename T>
template<typename U>
inline Vector3<T>& Vector3<T>::operator-=(U value)
{
	x -= value;
	y -= value;
	z -= value;

	return *this;
}

template<typename T>
template<typename U>
inline Vector3<T>& Vector3<T>::operator*=(U value)
{
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

template<typename T>
template<typename U>
inline Vector3<T>& Vector3<T>::operator/=(U value)
{
	x /= value;
	y /= value;
	z /= value;

	return *this;
}

template<typename T>
inline T& Vector3<T>::operator[](size_t index)
{
	if (index == 0)
	{
		return x;
	}

	if (index == 1)
	{
		return y;
	}

	return z;
}

template<typename T>
inline void Vector3<T>::Normalize()
{
	float magnitude = sqrt(x * x + y * y + z * z);

	if (magnitude == 0)
	{
		return;
	}

	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
}

template<typename T>
inline Vector3<T> Vector3<T>::Normalized() const
{
	Vector3<T> normalized(*this);
	normalized.Normalize();
	return normalized;
}

template<typename T>
inline float Vector3<T>::SquaredMagnitude() const
{
	return x * x + y * y + z * z;
}

template<typename T>
inline float Vector3<T>::Magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}
#pragma endregion

#pragma region UnraryOperators
template<typename T>
inline Vector3<T> operator+(const Vector3<T>& v)
{
	return v;
}

template<typename T>
inline Vector3<T> operator-(const Vector3<T>& v)
{
	return Vector3<T>(-v.x, -v.y, -v.z);
}
#pragma endregion

#pragma region BinaryOperators
template<typename T>
inline Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2)
{
	return Vector3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template<typename T>
inline Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2)
{
	return Vector3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template<typename T>
inline Vector3<T> operator*(const Vector3<T>& v1, const Vector3<T>& v2)
{
	return Vector3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template<typename T>
inline Vector3<T> operator/(const Vector3<T>& v1, const Vector3<T>& v2)
{
	return Vector3<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

template<typename T>
inline Vector3<T> operator+(const Vector3<T>& v, T value)
{
	return Vector3<T>(v.x + value, v.y + value, v.z + value);
}

template<typename T>
inline Vector3<T> operator-(const Vector3<T>& v, T value)
{
	return Vector3<T>(v.x - value, v.y - value, v.z - value);
}

template<typename T>
inline Vector3<T> operator*(const Vector3<T>& v, T scalar)
{
	return Vector3<T>(v.x * scalar, v.y * scalar, v.z * scalar);
}

template<typename T>
inline Vector3<T> operator/(const Vector3<T>& v, T scalar)
{
	return Vector3<T>(v.x / scalar, v.y / scalar, v.z / scalar);
}

template<typename T>
inline Vector3<T> operator+(T value, const Vector3<T>& v)
{
	return Vector3<T>(value + v.x, value + v.y, value + v.z);
}

template<typename T>
inline Vector3<T> operator-(T value, const Vector3<T>& v)
{
	return Vector3<T>(value - v.x, value - v.y, value - v.z);
}

template<typename T>
inline Vector3<T> operator*(T scalar, const Vector3<T>& v)
{
	return Vector3<T>(scalar * v.x, scalar * v.y, scalar * v.z);
}

template<typename T>
inline Vector3<T> operator/(T scalar, const Vector3<T>& v)
{
	return Vector3<T>(scalar / v.x, scalar / v.y, scalar / v.z);
}
#pragma endregion

#pragma region BooleanOperators
template<typename T>
inline bool operator==(const Vector3<T>& v1, const Vector3<T>& v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}

template <typename T>
inline bool operator!=(const Vector3<T>& v1, const Vector3<T>& v2)
{
	return (v1.x != v2.x || v1.y != v2.y || v1.z != v2.z);
}
#pragma endregion

// -- Types --
using Vector3ui = Vector3<unsigned int>;
using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;