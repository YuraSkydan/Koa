#pragma once
#include <cmath>

template<typename T>
struct Vector3;

template<typename T>
struct Vector2
{
	T x, y;

	Vector2();
	Vector2(T value);
	Vector2(T x, T y);
	
	template<typename U>
	Vector2(const Vector2<U>& other);
	
	template<typename U>
	Vector2(const Vector3<U>& other);

	template<typename U>
	Vector2<T>& operator=(const Vector2<U>& v);

	template<typename U>
	Vector2<T>& operator=(const Vector3<U>& v);

	template<typename U>
	Vector2<T>& operator+=(const Vector2<U>& v);

	template<typename U>
	Vector2<T>& operator-=(const Vector2<U>& v);

	template<typename U>
	Vector2<T>& operator*=(const Vector2<U>& v);

	template<typename U>
	Vector2<T>& operator/=(const Vector2<U>& v);

	template<typename U>
	Vector2<T>& operator=(U value);

	template<typename U>
	Vector2<T>& operator+=(U value);

	template<typename U>
	Vector2<T>& operator-=(U value);

	template<typename U>
	Vector2<T>& operator*=(U scalar);

	template<typename U>
	Vector2<T>& operator/=(U scalar);

	T& operator[](size_t index);

	Vector2<T> Normalized();
	void Normalize();
	float Magnitude() const;
};

#pragma region Methods
template<typename T>
Vector2<T>::Vector2()
{
	x = 0;
	y = 0;
}

template<typename T>
Vector2<T>::Vector2(T value)
{
	x = value;
	y = value;
}

template<typename T>
Vector2<T>::Vector2(T x, T y)
{
	this->x = x;
	this->y = y;
}

template<typename T>
template<typename U>
inline Vector2<T>::Vector2(const Vector2<U>& other)
{
	x = other.x;
	y = other.y;
}

template<typename T>
template<typename U>
inline Vector2<T>& Vector2<T>::operator=(const Vector2<U>& v)
{
	x = v.x;
	y = v.y;

	return *this;
}

template<typename T>
template<typename U>
inline Vector2<T>& Vector2<T>::operator+=(const Vector2<U>& v)
{
	x += v.x;
	y += v.y;

	return *this;
}

template<typename T>
template<typename U>
inline Vector2<T>& Vector2<T>::operator-=(const Vector2<U>& v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}

template<typename T>
template<typename U>
inline Vector2<T>& Vector2<T>::operator*=(const Vector2<U>& v)
{
	x *= v.x;
	y *= v.y;

	return *this;
}

template<typename T>
template<typename U>
inline Vector2<T>& Vector2<T>::operator/=(const Vector2<U>& v)
{
	x /= v.x;
	y /= v.y;

	return *this;
}

template<typename T>
template<typename U>
inline Vector2<T>& Vector2<T>::operator=(U value)
{
	x = value;
	y = value;

	return *this;
}

template<typename T>
template<typename U>
inline Vector2<T>& Vector2<T>::operator+=(U value)
{
	x += value;
	y += value;

	return *this;
}

template<typename T>
template<typename U>
inline Vector2<T>& Vector2<T>::operator-=(U value)
{
	x -= value;
	y -= value;

	return *this;
}

template<typename T>
template<typename U>
inline Vector2<T>& Vector2<T>::operator*=(U scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

template<typename T>
template<typename U>
inline Vector2<T>& Vector2<T>::operator/=(U scalar)
{
	x /= scalar;
	y /= scalar;
	
	return *this;
}

template<typename T>
inline T& Vector2<T>::operator[](size_t index)
{
	if (index == 0)
	{
		return x;
	}

	return y;
}

template<typename T>
inline Vector2<T> Vector2<T>::Normalized()
{
	Vector2<T> normalized(this);
	normalized.Normalize();
	return normalized;
}

template<typename T>
inline void Vector2<T>::Normalize()
{
	float magnitude = sqrt(x * x + y * y);

	if (magnitude == 0)
		return 0;

	x /= magnitude;
	y /= magnitude;
}

template<typename T>
inline float Vector2<T>::Magnitude() const
{
	return sqrt(x * x + y * y);
}
#pragma endregion

#pragma region UnaryOperators 
template<typename T>
inline Vector2<T> operator+(const Vector2<T>& v)
{
	return v;
}

template<typename T>
inline Vector2<T> operator-(const Vector2<T>& v)
{
	return Vector2<T>(-v.x, -v.y);
}
#pragma endregion

#pragma region BinaryOperators
template<typename T>
inline Vector2<T> operator+(const Vector2<T>& v1, const Vector2<U>& v2)
{
	return Vector2<T>(v1.x + v2.x, v1.y + v2.y);
}

template<typename T>
inline Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2)
{
	return Vector2<T>(v1.x - v2.x, v1.y - v2.y);
}

template<typename T>
inline Vector2<T> operator*(const Vector2<T>& v1, const Vector2<T>& v2)
{
	return Vector2<T>(v1.x * v2.x, v1.y * v2.y);
}

template<typename T>
inline Vector2<T> operator/(const Vector2<T>& v1, const Vector2<T>& v2)
{
	return Vector2<T>(v1.x / v2.x, v1.y / v2.y);
}


template<typename T>
inline Vector2<T> operator+(const Vector2<T>& v, T value)
{												  
	return Vector2<T>(v.x + value, v.y + value);
}												  
												  
template<typename T>							  
inline Vector2<T> operator-(const Vector2<T>& v, T value)
{
	return Vector2<T>(v.x - value, v.y - value);
}

template<typename T, typename U>
inline Vector2<T> operator*(const Vector2<T>& v, U scalar)
{
	return Vector2<T>(v.x * scalar, v.y * scalar);
}

template<typename T>
inline Vector2<T> operator/(const Vector2<T>& v, T scalar)
{
	return Vector2<T>(v.x / scalar, v.y / scalar);
}


template<typename T>
inline Vector2<T> operator+(T value, const Vector2<T>& v)
{
	return Vector2<T>(value + v.x, value + v.y);
}

template<typename T>
inline Vector2<T> operator-(T value, const Vector2<T>& v)
{
	return Vector2<T>(value - v.x, value - v.y);
}

template<typename T>
inline Vector2<T> operator*(T scalar, const Vector2<T>& v)
{
	return Vector2<T>(scalar * v.x, scalar * v.y);
}

template<typename T>
inline Vector2<T> operator/(T scalar, const Vector2<T>& v)
{
	return Vector2<T>(scalar / v.x, scalar / v.y);
}
#pragma endregion 

#pragma region BooleanOperators
template<typename T>
inline bool operator==(const Vector2<T>& v1, const Vector2<T>& v2)
{
	return ((v1.x == v2.x) && (v1.y == v2.y));
}

template<typename T>
inline bool operator!=(const Vector2<T>& v1, const Vector2<T>& v2)
{
	return ((v1.x != v2.x) || (v1.y != v2.y));
}
#pragma endregion

// -- Types -- 
using Vector2ui = Vector2<unsigned int>;
using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;