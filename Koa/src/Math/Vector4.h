#pragma once
#include <cmath>

template<typename T>
struct Vector2;

template<typename T>
struct Vector4
{
	T x, y, z, w;

	Vector4();
	Vector4(T value);
	Vector4(T x, T y, T z, T w);

	template<typename U>
	Vector4(const Vector4<U>& other);

	template<typename U>
	Vector4(const Vector3<U>& other);

	template<typename U>
	Vector4(const Vector2<U>& other);

	template<typename U>
	Vector4<T>& operator=(const Vector2<U>& v);

	template<typename U>
	Vector4<T>& operator=(const Vector3<U>& v);

	template<typename U>
	Vector4<T>& operator=(const Vector4<U>& v);

	template<typename U>
	Vector4<T>& operator+=(const Vector4<U>& v);

	template<typename U>
	Vector4<T>& operator-=(const Vector4<U>& v);

	template<typename U>
	Vector4<T>& operator*=(const Vector4<U>& v);

	template<typename U>
	Vector4<T>& operator/=(const Vector4<U>& v);

	template<typename U>
	Vector4<T>& operator=(U value);

	template<typename U>
	Vector4<T>& operator+=(U value);

	template<typename U>
	Vector4<T>& operator-=(U value);

	template<typename U>
	Vector4<T>& operator*=(U value);

	template<typename U>
	Vector4<T>& operator/=(U value);

	T& operator[](size_t index);

	void Normalize();
	Vector4<T> Normalized() const;
	float SquaredMagnitude() const;
	float Magnitude() const;
};
#pragma region Methods
template<typename T>
inline Vector4<T>::Vector4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

template<typename T>
inline Vector4<T>::Vector4(T value)
{
	x = value;
	y = value;
	z = value;
	w = value;
}

template<typename T>
inline Vector4<T>::Vector4(T x, T y, T z, T w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

template<typename T>
template<typename U>
inline Vector4<T>::Vector4(const Vector4<U>& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

template<typename T>
template<typename U>
inline Vector4<T>& Vector4<T>::operator=(const Vector4<U>& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;

	return *this;
}

template<typename T>
template<typename U>
inline Vector4<T>& Vector4<T>::operator+=(const Vector4<U>& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;

	return *this;
}

template<typename T>
template<typename U>
inline Vector4<T>& Vector4<T>::operator-=(const Vector4<U>& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;

	return *this;
}

template<typename T>
template<typename U>
inline Vector4<T>& Vector4<T>::operator*=(const Vector4<U>& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;

	return *this;
}

template<typename T>
template<typename U>
inline Vector4<T>& Vector4<T>::operator/=(const Vector4<U>& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;

	return *this;
}

template<typename T>
template<typename U>
inline Vector4<T>& Vector4<T>::operator=(U value)
{
	x = value;
	y = value;
	z = value;
	w = value;

	return *this;
}

template<typename T>
template<typename U>
inline Vector4<T>& Vector4<T>::operator+=(U value)
{
	x += value;
	y += value;
	z += value;
	w += value;

	return *this;
}

template<typename T>
template<typename U>
inline Vector4<T>& Vector4<T>::operator-=(U value)
{
	x -= value;
	y -= value;
	z -= value;
	w -= value;

	return *this;
}

template<typename T>
template<typename U>
inline Vector4<T>& Vector4<T>::operator*=(U value)
{
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

template<typename T>
template<typename U>
inline Vector4<T>& Vector4<T>::operator/=(U value)
{
	x /= value;
	y /= value;
	z /= value;
	w /= value;

	return *this;
}

template<typename T>
inline T& Vector4<T>::operator[](size_t index)
{
	switch (index)
	{
	case 0:
		return x;
	
	case 1:
		return y;
	
	case 2:
		return z;

	default:
		return w;
	}
}

template<typename T>
inline void Vector4<T>::Normalize()
{
	float magnitude = sqrt(x * x + y * y + z * z + w * w);

	if (magnitude == 0)
	{
		return;
	}

	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
	w /= magnitude;
}

template<typename T>
inline Vector4<T> Vector4<T>::Normalized() const
{
	Vector4<T> normalized(*this);
	normalized.Normalize();
	return normalized;
}

template<typename T>
inline float Vector4<T>::SquaredMagnitude() const
{
	return x * x + y * y + z * z + w * w;
}

template<typename T>
inline float Vector4<T>::Magnitude() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}
#pragma endregion

#pragma region UnraryOperators
template<typename T>
inline Vector4<T> operator+(const Vector4<T>& v)
{
	return *this;
}

template<typename T>
inline Vector4<T> operator-(const Vector4<T>& v)
{
	return Vector4<T>(-v.x, -v.y, -v.z, -v.w);
}
#pragma endregion

#pragma region BinaryOperators
template<typename T>
inline Vector4<T> operator+(const Vector4<T>& v1, const Vector4<T>& v2)
{
	return Vector4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

template<typename T>
inline Vector4<T> operator-(const Vector4<T>& v1, const Vector4<T>& v2)
{
	return Vector4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

template<typename T>
inline Vector4<T> operator*(const Vector4<T>& v1, const Vector4<T>& v2)
{
	return Vector4<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

template<typename T>
inline Vector4<T> operator/(const Vector4<T>& v1, const Vector4<T>& v2)
{
	return Vector4<T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

template<typename T>
inline Vector4<T> operator+(const Vector4<T>& v, T value)
{
	return Vector4<T>(v.x + value, v.y + value, v.z + value, v.w + value);
}

template<typename T>
inline Vector4<T> operator-(const Vector4<T>& v, T value)
{
	return Vector4<T>(v.x - value, v.y - value, v.z - value, v.w - value);
}

template<typename T>
inline Vector4<T> operator*(const Vector4<T>& v, T scalar)
{
	return Vector4<T>(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
}

template<typename T>
inline Vector4<T> operator/(const Vector4<T>& v, T scalar)
{
	return Vector4<T>(v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar);
}

template<typename T>
inline Vector4<T> operator+(T value, const Vector4<T>& v)
{
	return Vector4<T>(value + v.x, value + v.y, value + v.z, value + v.w);
}

template<typename T>
inline Vector4<T> operator-(T value, const Vector4<T>& v)
{
	return Vector4<T>(value - v.x, value - v.y, value - v.z, value - v.w);
}

template<typename T>
inline Vector4<T> operator*(T scalar, const Vector4<T>& v)
{
	return Vector4<T>(scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w);
}

template<typename T>
inline Vector4<T> operator/(T scalar, const Vector4<T>& v)
{
	return Vector4<T>(scalar / v.x, scalar / v.y, scalar / v.z, scalar / v.w);
}
#pragma endregion

#pragma region BooleanOperators
template<typename T>
inline bool operator==(const Vector4<T>& v1, const Vector4<T>& v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w);
}

template <typename T>
inline bool operator!=(const Vector4<T>& v1, const Vector4<T>& v2)
{
	return (v1.x != v2.x || v1.y != v2.y || v1.z != v2.z);
}
#pragma endregion

// -- Types --
using Vector4ui = Vector4<unsigned int>;
using Vector4f = Vector4<float>;
using Vector4i = Vector4<int>;