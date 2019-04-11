/**
* Project CloudMath
* @author CloudTech
* @version 1.0.0
*/

#pragma once
#ifndef _MATRIX2_INL
#define _MATRIX2_INL

#include "CloudMath/stdafx.h"
#include "CloudMath/Vector/Vector2.h"

namespace CloudMath
{
	template <typename T>
	const Matrix2<T> Matrix2<T>::Identity = Matrix2<T>(1.0f, 0.0f,
	                                                   0.0f, 1.0f);

#pragma region Constructors & Assignment

	template <typename T>
	Matrix2<T>::Matrix2()
		: Matrix2<T>(Identity) { }

	template <typename T>
	Matrix2<T>::Matrix2(T p_value)
	{
		for (T& element : elements)
			element = p_value;
	}

	template <typename T>
	Matrix2<T>::Matrix2(T p_element1, T p_element2, T p_element3, T p_element4)
	{
		elements[0] = p_element1;
		elements[1] = p_element2;
		elements[2] = p_element3;
		elements[3] = p_element4;
	}

	template <typename T>
	Matrix2<T>::Matrix2(const Matrix2<T>& p_other)
	{
		memcpy(this->elements, p_other.elements, 4 * sizeof(T));
	}

	template <typename T>
	Matrix2<T>::Matrix2(Matrix2<T>&& p_other) noexcept
	{
		memmove(this->elements, p_other.elements, 4 * sizeof(T));
	}

	template <typename T>
	Matrix2<T>& Matrix2<T>::operator=(const Matrix2<T>& p_other)
	{
		memcpy(this->elements, p_other.elements, 4 * sizeof(T));
		return *this;
	}

	template <typename T>
	Matrix2<T>& Matrix2<T>::operator=(Matrix2<T>&& p_other) noexcept
	{
		memmove(this->elements, p_other.elements, 4 * sizeof(T));
		return *this;
	}

#pragma endregion

#pragma region Tests & Comparisons

	template <typename T>
	bool Matrix2<T>::IsIdentity() const
	{
		return memcmp(elements, Matrix2<T>::Identity, 4 * sizeof(T)) == 0;
	}

	template <typename T>
	bool Matrix2<T>::operator==(Matrix2<T>& p_other) const
	{
		return memcmp(elements, p_other.elements, 4 * sizeof(T)) == 0;;
	}
#pragma endregion

#pragma region Arithmetic Operations
#pragma region Addition

	template <typename T>
	Matrix2<T>& Matrix2<T>::Add(T p_scalar)
	{
		for (T& element : elements)
		{
			element += p_scalar;
		}
		return *this;
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::Add(const Matrix2<T>& p_left, T p_scalar)
	{
		Matrix2<T> result(p_left);
		for (T& element : result.elements)
		{
			element += p_scalar;
		}
		return result;
	}

	template <typename T>
	Matrix2<T>& Matrix2<T>::Add(const Matrix2<T>& p_other)
	{
		for (uint8_t i = 0; i < 4; ++i)
			elements[i] += p_other.elements[i];

		return *this;
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::Add(const Matrix2<T>& p_left, const Matrix2<T>& p_right)
	{
		Matrix2<T> result = p_left;
		for (uint8_t i = 0; i < 4; ++i)
			result.elements[i] += p_right.elements[i];
		return result;
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::operator+(const Matrix2<T>& p_other) const
	{
		return Matrix2<T>::Add(*this, p_other);
	}

	template <typename T>
	Matrix2<T>& Matrix2<T>::operator+=(const Matrix2<T>& p_other)
	{
		return this->Add(p_other);
	}
#pragma endregion

#pragma region Subtraction

	template <typename T>
	Matrix2<T>& Matrix2<T>::Subtract(T p_scalar)
	{
		for (T& element : elements)
			element -= p_scalar;

		return *this;
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::Subtract(const Matrix2<T>& p_left, T p_scalar)
	{
		Matrix2<T> result(p_left);
		for (T& element : result.elements)
			element -= p_scalar;
		return result;
	}

	template <typename T>
	Matrix2<T>& Matrix2<T>::Subtract(const Matrix2<T>& p_other)
	{
		for (uint8_t i = 0; i < 4; ++i)
			elements[i] -= p_other.elements[i];

		return *this;
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::Subtract(const Matrix2<T>& p_left, const Matrix2<T>& p_right)
	{
		Matrix2<T> result(p_left);
		for (uint8_t i = 0; i < 4; ++i)
			result.elements[i] -= p_right.elements[i];

		return result;
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::operator-(const Matrix2<T>& p_other) const
	{
		return Matrix2<T>::Subtract(*this, p_other);
	}

	template <typename T>
	Matrix2<T>& Matrix2<T>::operator-=(const Matrix2<T>& p_other)
	{
		return this->Subtract(p_other);
	}

#pragma endregion

#pragma region Scalar Product

	template <typename T>
	Matrix2<T>& Matrix2<T>::Multiply(T p_scalar)
	{
		for (T& element : elements)
			element *= p_scalar;
		return *this;
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::Multiply(const Matrix2<T>& p_left, T p_scalar)
	{
		Matrix2<T> result(p_left);
		for (T& element : result.elements)
			element *= p_scalar;

		return result;
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::operator*(T p_scalar) const
	{
		return Matrix2<T>::Multiply(*this, p_scalar);
	}

	template <typename T>
	Matrix2<T>& Matrix2<T>::operator*=(T p_scalar)
	{
		return this->Multiply(p_scalar);
	}

#pragma endregion

#pragma region Vector Product

	template <typename T>
	Vector2<T> Matrix2<T>::Multiply(const Vector2<T>& p_vector) const
	{
		Vector2<T> result;

		result.x = (elements[0] * p_vector.x) + (elements[2] * p_vector.y);
		result.y = (elements[1] * p_vector.x) + (elements[3] * p_vector.y);

		return result;
	}

	template <typename T>
	Vector2<T> Matrix2<T>::Multiply(const Matrix2<T>& p_matrix, const Vector2<T>& p_vector)
	{
		return p_matrix.Multiply(p_vector);
	}

	template <typename T>
	Vector2<T> Matrix2<T>::operator*(const Vector2<T>& p_vector) const
	{
		return this->Multiply(p_vector);
	}

#pragma endregion

#pragma region Matrix Product

	template <typename T>
	Matrix2<T>& Matrix2<T>::Multiply(const Matrix2<T>& p_other)
	{
		Matrix2<T> result;

		result.elements[0] = (elements[0] * p_other.elements[0] + elements[2] * p_other.elements[1]);
		result.elements[1] = (elements[1] * p_other.elements[0] + elements[3] * p_other.elements[1]);

		result.elements[2] = (elements[0] * p_other.elements[2] + elements[2] * p_other.elements[3]);
		result.elements[3] = (elements[1] * p_other.elements[2] + elements[3] * p_other.elements[3]);

		return *this = result;
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::Multiply(const Matrix2<T>& p_left, const Matrix2<T>& p_right)
	{
		Matrix2<T> result((p_left.elements[0] * p_right.elements[0] + p_left.elements[2] * p_right.elements[1]),
		                  (p_left.elements[1] * p_right.elements[0] + p_left.elements[3] * p_right.elements[1]),
		                  (p_left.elements[0] * p_right.elements[2] + p_left.elements[2] * p_right.elements[3]),
		                  (p_left.elements[1] * p_right.elements[2] + p_left.elements[3] * p_right.elements[3]));

		return result;
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::operator*(const Matrix2<T>& p_other) const
	{
		return Matrix2<T>::Multiply(*this, p_other);
	}

	template <typename T>
	Matrix2<T>& Matrix2<T>::operator*=(const Matrix2<T>& p_other)
	{
		return this->Multiply(p_other);
	}

#pragma endregion

#pragma region Scalar Division

	template <typename T>
	Matrix2<T>& Matrix2<T>::Divide(T p_scalar)
	{
		if (p_scalar == 0)
			throw std::logic_error("Division by 0");

		for (T& element : elements)
			element /= p_scalar;
		return *this;
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::Divide(const Matrix2<T>& p_left, T p_scalar)
	{
		if (p_scalar == 0)
			throw std::logic_error("Division by 0");

		Matrix2<T> result(p_left);
		for (T& element : result.elements)
			element /= p_scalar;
		return result;
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::operator/(T p_scalar) const
	{
		return Matrix2<T>::Divide(*this, p_scalar);
	}

	template <typename T>
	Matrix2<T>& Matrix2<T>::operator/=(T p_scalar)
	{
		return this->Divide(p_scalar);
	}

#pragma endregion

#pragma region Matrix Division

	template <typename T>
	Matrix2<T>& Matrix2<T>::Divide(const Matrix2<T>& p_other)
	{
		return *this *= p_other.Inverse();
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::Divide(const Matrix2<T>& p_left, const Matrix2<T>& p_right)
	{
		return p_left * Matrix2<T>::Inverse(p_right);
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::operator/(const Matrix2<T>& p_other)
	{
		return Matrix2<T>::Divide(*this, p_other);
	}

	template <typename T>
	Matrix2<T>& Matrix2<T>::operator/=(const Matrix2<T>& p_other)
	{
		return this->Divide(p_other);
	}

#pragma endregion
#pragma endregion

#pragma region Matrix Operations

	template <typename T>
	T Matrix2<T>::Determinant() const
	{
		return (elements[0] * elements[3]) - (elements[1] * elements[2]);
	}

	template <typename T>
	T Matrix2<T>::Determinant(const Matrix2<T>& p_matrix)
	{
		return (p_matrix.elements[0] * p_matrix.elements[3] - p_matrix.elements[1] * p_matrix.elements[2]);
	}

	template <typename T>
	Matrix2<T>& Matrix2<T>::Transpose()
	{
		std::swap(elements[1], elements[2]);
		return *this;
	}

	template <typename T>
	constexpr Matrix2<T> Matrix2<T>::Transpose(const Matrix2<T>& p_matrix)
	{
		return Matrix2<T>(p_matrix.elements[0], p_matrix.elements[1],
		                  p_matrix.elements[2], p_matrix.elements[3]);
	}

	template <typename T>
	constexpr Matrix2<T> Matrix2<T>::Cofactor() const
	{
		return Matrix2<T>(this->elements[3], -this->elements[2],
		                  -this->elements[1], this->elements[0]);
	}

	template <typename T>
	constexpr Matrix2<T> Matrix2<T>::Cofactor(const Matrix2<T>& p_matrix)
	{
		return Matrix2<T>(p_matrix.elements[3], -p_matrix.elements[2],
		                  -p_matrix.elements[1], p_matrix.elements[0]);
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::Adjoint() const
	{
		return Matrix2<T>(this->elements[3], -this->elements[1],
			-this->elements[2], this->elements[0]);
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::Adjoint(const Matrix2<T>& p_matrix)
	{
		return Matrix2<T>(p_matrix.elements[3], -p_matrix.elements[2],
			-p_matrix.elements[1], p_matrix.elements[0]);
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::Inverse() const
	{
		T determinant = this->Determinant();
		if (determinant == 0)
			throw std::logic_error("Division by 0");

		return this->Adjoint() / determinant;
	}

	template <typename T>
	Matrix2<T> Matrix2<T>::Inverse(const Matrix2<T>& p_matrix)
	{
		T determinant = p_matrix.Determinant();
		if (determinant == 0)
			throw std::logic_error("Division by 0");

		return p_matrix.Adjoint() / determinant;
	}
#pragma endregion

#pragma region Conversions

	template <typename T>
	std::string Matrix2<T>::ToString() const
	{
		return std::string(std::to_string(elements[0]) + "\t" + std::to_string(elements[2]) + "\n"
			+ std::to_string(elements[1]) + "\t" + std::to_string(elements[3]));
	}

	template <typename T>
	std::string Matrix2<T>::ToString(const Matrix2<T>& p_matrix)
	{
		return p_matrix.ToString();
	}

	template <typename T>
	T* Matrix2<T>::ToArray() const
	{
		return elements;
	}

	template <typename T>
	T* Matrix2<T>::ToArray(const Matrix2<T>& p_matrix)
	{
		return p_matrix.elements;
	}

	template <typename T>
	Vector2<T> Matrix2<T>::GetRow(uint8_t p_row) const
	{
		if (p_row >= 2)
			throw std::out_of_range("Invalid index : " + std::to_string(p_row) + " is out of range");

		return Vector2<T>(elements[p_row], elements[p_row + 2]);
	}

	template <typename T>
	Vector2<T> Matrix2<T>::GetColumn(uint8_t p_column) const
	{
		if (p_column >= 2)
			throw std::out_of_range("Invalid index : " + std::to_string(p_column) + " is out of range");

		return Vector2<T>(elements[p_column], elements[p_column + 1]);
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& p_stream, const Matrix2<T>& p_matrix)
	{
		p_stream << p_matrix.elements[0] << "\t" << p_matrix.elements[2] << "\n" << p_matrix.elements[1] << "\t" <<
			p_matrix.elements[3];
		return p_stream;
	}

	template <typename T>
	constexpr Matrix2<T> operator*(T p_scalar, const Matrix2<T>& p_matrix)
	{
		return p_matrix * p_scalar;
	}

#pragma endregion
}

#endif // !#ifndef _MATRIX2_INL
