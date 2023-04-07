#pragma once
#include "Vector2.h"
#include "Vector3.h"

template<typename T, size_t SIZE>
struct Matrix
{
	T elements[SIZE][SIZE];

	Matrix();
	Matrix(T diagonal);

	template<size_t S>
	Matrix(const Matrix<T, S>& other);

	template<size_t S>
	Matrix<T, SIZE>& operator=(const Matrix<T, S>& other);

	template<typename U>
	Matrix<T, SIZE>& operator+=(const Matrix<U, SIZE>& m);

	template<typename U>
	Matrix<T, SIZE>& operator-=(const Matrix<U, SIZE>& m);

	template<typename U>
	Matrix<T, SIZE>& operator*=(const Matrix<U, SIZE>& m);

	template<typename U>
	Matrix<T, SIZE>& operator+=(U scalar);

	template<typename U>
	Matrix<T, SIZE>& operator-=(U scalar);

	template<typename U>
	Matrix<T, SIZE>& operator*=(U scalar);

	T* operator[](size_t index);
	const T* operator[](size_t index) const;

	Matrix<T, SIZE> Transpose() const;
};

#pragma region Methods
template<typename T, size_t SIZE>
inline Matrix<T, SIZE>::Matrix()
	: elements{ 0 }
{ }

template<typename T, size_t SIZE>
inline Matrix<T, SIZE>::Matrix(T diagonal)
	: elements{ 0 }
{
	for (size_t i = 0; i < SIZE; i++)
		elements[i][i] = diagonal;
}

template<typename T, size_t SIZE>
template<size_t S>
inline Matrix<T, SIZE>::Matrix(const Matrix<T, S>& other)
{
	size_t size = (S <= SIZE) ? S : SIZE;

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
			elements[i][j] = other[i][j];
	}
}

template<typename T, size_t SIZE>
template<size_t S>
inline Matrix<T, SIZE>& Matrix<T, SIZE>::operator=(const Matrix<T, S>& other)
{
	size_t size = (S <= SIZE) ? S : SIZE;

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
			elements[i][j] = other[i][j];
	}

	return *this;
}

template<typename T, size_t SIZE>
template<typename U>
inline Matrix<T, SIZE>& Matrix<T, SIZE>::operator+=(const Matrix<U, SIZE>& m)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
			elements[i][j] += m[i][j];
	}

	return this;
}

template<typename T, size_t SIZE>
template<typename U>
inline Matrix<T, SIZE>& Matrix<T, SIZE>::operator-=(const Matrix<U, SIZE>& m)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
			elements[i][j] -= m[i][j];
	}

	return this;
}

template<typename T, size_t SIZE>
template<typename U>
inline Matrix<T, SIZE>& Matrix<T, SIZE>::operator*=(const Matrix<U, SIZE>& m)
{
	*this = *this * m;
}

template<typename T, size_t SIZE>
template<typename U>
inline Matrix<T, SIZE>& Matrix<T, SIZE>::operator+=(U scalar)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
			elements[i][j] += scalar;
	}

	return this;
}

template<typename T, size_t SIZE>
template<typename U>
inline Matrix<T, SIZE>& Matrix<T, SIZE>::operator-=(U scalar)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
			elements[i][j] -= scalar;
	}

	return this;
}

template<typename T, size_t SIZE>
template<typename U>
inline Matrix<T, SIZE>& Matrix<T, SIZE>::operator*=(U scalar)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
			elements[i][j] *= scalar;
	}

	return this;
}

template<typename T, size_t SIZE>
inline T* Matrix<T, SIZE>::operator[](size_t index)
{
	return elements[index];
}

template<typename T, size_t SIZE>
inline const T* Matrix<T, SIZE>::operator[](size_t index) const
{
	return elements[index];
}

template<typename T, size_t SIZE>
inline Matrix<T, SIZE> Matrix<T, SIZE>::Transpose() const
{
	Matrix<T, SIZE> transpose;
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
			transpose[i][j] = elements[j][i];
	}

	return transpose;
}
#pragma endregion

#pragma region UnaryOperators
template<typename T, size_t SIZE>
inline Matrix<T, SIZE>& operator+(const Matrix<T, SIZE>& m)
{
	return m;
}

template<typename T, size_t SIZE>
inline Matrix<T, SIZE> operator-(const Matrix<T, SIZE>& m)
{
	Matrix<T, SIZE> result;
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
		{
			result[i][j] = -m[i][j];
		}
	}

	return result;
}
#pragma endregion

#pragma region BinaryOperators
template<typename T, size_t SIZE>
inline Matrix<T, SIZE> operator+(const Matrix<T, SIZE>& m1, const Matrix<T, SIZE>& m2)
{
	Matrix<T, SIZE> temp;

	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
			temp[i][j] = m1[i][j] + m2[i][j];
	}

	return temp;
}

template<typename T, size_t SIZE>
inline Matrix<T, SIZE> operator-(const Matrix<T, SIZE>& m1, const Matrix<T, SIZE>& m2)
{
	Matrix<T, SIZE> temp;

	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
			temp[i][j] = m1[i][j] - m2[i][j];
	}

	return temp;
}

template<typename T, size_t SIZE>
inline Matrix<T, SIZE> operator*(const Matrix<T, SIZE>& m1, const Matrix<T, SIZE>& m2)
{
	Matrix<T, SIZE> temp;

	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
		{
			for (size_t k = 0; k < SIZE; k++)
			{
				temp[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}

	return temp;
}

template<typename T, size_t SIZE>
inline Matrix<T, SIZE> operator+(const Matrix<T, SIZE>& m, T scalar)
{
	Matrix<T, SIZE> temp;

	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
			temp[i][j] = m[i][j] + scalar;
	}

	return temp;
}

template<typename T, size_t SIZE>
inline Matrix<T, SIZE> operator-(const Matrix<T, SIZE>& m, T scalar)
{
	Matrix<T, SIZE> temp;

	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
			temp[i][j] = m[i][j] - scalar;
	}

	return temp;
}

template<typename T, size_t SIZE>
inline Matrix<T, SIZE> operator*(const Matrix<T, SIZE>& m, T scalar)
{
	Matrix<T, SIZE> temp;

	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
		{
			temp[i][j] += m[i][j] * scalar;
		}
	}

	return temp;
}

template<typename T, size_t SIZE>
inline Matrix<T, SIZE> operator+(T scalar, const Matrix<T, SIZE>& m)
{
	Matrix<T, SIZE> temp;

	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
			temp[i][j] = scalar + m[i][j];
	}

	return temp;
}

template<typename T, size_t SIZE>
inline Matrix<T, SIZE> operator-(T scalar, const Matrix<T, SIZE>& m)
{
	Matrix<T, SIZE> temp;

	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
			temp[i][j] = scalar - m[i][j];
	}

	return temp;
}

template<typename T, size_t SIZE>
inline Matrix<T, SIZE> operator*(T scalar, const Matrix<T, SIZE>& m)
{
	Matrix<T, SIZE> temp;

	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
		{
			temp[i][j] += m[i][j] * scalar;
		}
	}

	return temp;
}
#pragma endregion

#pragma region BoleanOperators
template<typename T, size_t SIZE>
inline bool operator==(const Matrix<T, SIZE>& m1, const Matrix<T, SIZE>& m2)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
		{
			if (m1[i][j] != m2[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

template<typename T, size_t SIZE>
inline bool operator!=(const Matrix<T, SIZE>& m1, const Matrix<T, SIZE>& m2)
{
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
		{
			if (m1[i][j] != m2[i][j])
			{
				return true;
			}
		}
	}

	return false;
}
#pragma endregion

#pragma region Matrix4x4
template<typename T>
inline Vector3<T> operator*(const Matrix<T, 4>& m, const Vector3<T>& v)
{
	Vector3<T> result;
	result.x = (m[0][0] * v.x) + (m[0][1] * v.y) + (m[0][2] * v.z);
	result.y = (m[1][0] * v.x) + (m[1][1] * v.y) + (m[1][2] * v.z);
	result.z = (m[2][0] * v.x) + (m[2][1] * v.y) + (m[2][2] * v.z);

	return result;
}
#pragma endregion

#pragma region Matrix3x3
template<typename T>
inline Vector3<T> operator*(const Matrix<T, 3>& m, const Vector3<T>& v)
{
	Vector3<T> result;
	result.x = (m[0][0] * v.x) + (m[0][1] * v.y) + (m[0][2] * v.z);
	result.y = (m[1][0] * v.x) + (m[1][1] * v.y) + (m[1][2] * v.z);
	result.z = (m[2][0] * v.x) + (m[2][1] * v.y) + (m[2][2] * v.z);

	return result;
}

template<typename T>
inline Vector2<T> operator*(const Matrix<T, 3>& m, const Vector2<T>& v)
{
	Vector2<T> result;
	result.x = (m[0][0] * v.x) + (m[0][1] * v.y);
	result.y = (m[1][0] * v.x) + (m[1][1] * v.y);

	return result;
}
#pragma endregion

#pragma region Matrix2x2
template<typename T>
inline Vector2<T> operator*(const Matrix<T, 2>& m, const Vector2<T>& v)
{
	Vector2<T> vec;
	vec.x = (m[0][0] * v.x) + (m[0][1] * v.y);
	vec.y = (m[1][0] * v.x) + (m[1][1] * v.y);
	return vec;
}
#pragma endregion

// -------- Define Types ----------
using Matrix2x2f = Matrix<float, 2>;
using Matrix3x3f = Matrix<float, 3>;
using Matrix4x4f = Matrix<float, 4>;