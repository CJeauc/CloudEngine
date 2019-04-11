/**
* Project CloudMath
* @author CloudTech
* @version 1.0.0
*/

#pragma once
#ifndef _MATRIX4_INL
#define _MATRIX4_INL

#include "CloudMath/stdafx.h"
#include "Matrix4.h"

namespace CloudMath
{
	template <typename T>
	const Matrix4<T> Matrix4<T>::Identity = Matrix4<T>(1.f, 0.f, 0.f, 0.f,
	                                                   0.f, 1.f, 0.f, 0.f,
	                                                   0.f, 0.f, 1.f, 0.f,
	                                                   0.f, 0.f, 0.f, 1.f);

#pragma region Constructor & Assignement

	template <typename T>
	constexpr Matrix4<T>::Matrix4()
	{
		memcpy(this->elements, Matrix4<T>::Identity.elements, 16 * sizeof(T));
	}

	template <typename T>
	constexpr Matrix4<T>::Matrix4(T p_value)
	{
		for (T& element : elements)
			element = p_value;
	}

	template <typename T>
	constexpr Matrix4<T>::Matrix4(T p_element1, T p_element2, T p_element3, T p_element4,
	                    T p_element5, T p_element6, T p_element7, T p_element8,
	                    T p_element9, T p_element10, T p_element11, T p_element12,
	                    T p_element13, T p_element14, T p_element15, T p_element16)
	{
		elements[0] = p_element1;
		elements[1] = p_element2;
		elements[2] = p_element3;
		elements[3] = p_element4;

		elements[4] = p_element5;
		elements[5] = p_element6;
		elements[6] = p_element7;
		elements[7] = p_element8;

		elements[8] = p_element9;
		elements[9] = p_element10;
		elements[10] = p_element11;
		elements[11] = p_element12;

		elements[12] = p_element13;
		elements[13] = p_element14;
		elements[14] = p_element15;
		elements[15] = p_element16;
	}

	template <typename T>
	constexpr Matrix4<T>::Matrix4(const Matrix4<T>& p_other)
	{
		memcpy(this->elements, p_other.elements, 16 * sizeof(T));
	}

	template <typename T>
	constexpr Matrix4<T>::Matrix4(Matrix4<T>&& p_other) noexcept
	{
		memmove(this->elements, p_other.elements, 16 * sizeof(T));
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::operator=(const Matrix4<T>& p_other)
	{
		memcpy(this->elements, p_other.elements, 16 * sizeof(T));
		return *this;
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::operator=(Matrix4<T>&& p_other) noexcept
	{
		memmove(this->elements, p_other.elements, 16 * sizeof(T));
		return *this;
	}
#pragma endregion

#pragma region Arithmetic Operation

#pragma region Addition
	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::Add(const Matrix4<T>& p_other)
	{
		for (int8_t i = 0; i < 16; i++)
			this->elements[i] += p_other.elements[i];
		return *this;
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::Add(const Matrix4<T>& p_left, const Matrix4<T>& p_right)
	{
		Matrix4<T> result(p_left);
		for (int8_t i = 0; i < 16; i++)
			result.elements[i] += p_right.elements[i];
		return result;
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::operator+(const Matrix4<T>& p_other) const
	{
		return Add(*this, p_other);
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::operator+=(const Matrix4<T>& p_other)
	{
		return this->Add(p_other);
	}

#pragma endregion
#pragma region Substration

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::Subtract(const Matrix4<T>& p_other)
	{
		for (int8_t i = 0; i < 16; ++i)
			this->elements[i] -= p_other.elements[i];
		return *this;
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::Subtract(const Matrix4<T>& p_left, const Matrix4<T>& p_right)
	{
		Matrix4<T> result(p_left);
		for (int8_t i = 0; i < 16; ++i)
			result.elements[i] -= p_right.elements[i];
		return result;
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::operator-(const Matrix4<T>& p_other) const
	{
		return Subtract(*this, p_other);
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::operator-=(const Matrix4<T>& p_other)
	{
		return this->Subtract(p_other);
	}
#pragma endregion
#pragma region Multiplication

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::Multiply(T p_scalar)
	{
		for (T& element : elements)
			element *= p_scalar;
		return *this;
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::Multiply(const Matrix4<T>& p_left, T p_scalar)
	{
		Matrix4<T> result(p_left);
		for (T& element : result.elements)
			element *= p_scalar;
		return result;
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::operator*(T p_scalar) const
	{
		return Multiply(*this, p_scalar);
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::operator*=(T p_scalar)
	{
		return this->Multiply(p_scalar);
	}

	template <typename T>
	constexpr Vector4<T> Matrix4<T>::Multiply(const Vector4<T>& p_vector) const
	{
		Vector4<T> multiply;

		multiply.x = ((this->elements[0] * p_vector.x) + (this->elements[4] * p_vector.y) + (this->elements[8] *
			p_vector.z) + (this->elements[12] * p_vector.w));
		multiply.y = ((this->elements[1] * p_vector.x) + (this->elements[5] * p_vector.y) + (this->elements[9] *
			p_vector.z) + (this->elements[13] * p_vector.w));
		multiply.z = ((this->elements[2] * p_vector.x) + (this->elements[6] * p_vector.y) + (this->elements[10] *
			p_vector.z) + (this->elements[14] * p_vector.w));
		multiply.w = ((this->elements[3] * p_vector.x) + (this->elements[7] * p_vector.y) + (this->elements[11] *
			p_vector.z) + (this->elements[15] * p_vector.w));

		return multiply;
	}

	template <typename T>
	constexpr Vector4<T> Matrix4<T>::Multiply(const Matrix4<T>& p_matrix, const Vector4<T>& p_vector)
	{
		Vector4<T> multiply;

		multiply.x = ((p_matrix.elements[0] * p_vector.x) + (p_matrix.elements[4] * p_vector.y) + (p_matrix.elements[8]
			* p_vector.z) + (p_matrix.elements[12] * p_vector.w));
		multiply.y = ((p_matrix.elements[1] * p_vector.x) + (p_matrix.elements[5] * p_vector.y) + (p_matrix.elements[9]
			* p_vector.z) + (p_matrix.elements[13] * p_vector.w));
		multiply.z = ((p_matrix.elements[2] * p_vector.x) + (p_matrix.elements[6] * p_vector.y) + (p_matrix.elements[10]
			* p_vector.z) + (p_matrix.elements[14] * p_vector.w));
		multiply.w = ((p_matrix.elements[3] * p_vector.x) + (p_matrix.elements[7] * p_vector.y) + (p_matrix.elements[11]
			* p_vector.z) + (p_matrix.elements[15] * p_vector.w));

		return multiply;
	}

	template <typename T>
	constexpr Vector4<T> Matrix4<T>::operator*(const Vector4<T>& p_vector)
	{
		return Multiply(*this, p_vector);
	}

	template <typename T>
	constexpr Vector4<T>& Matrix4<T>::operator*=(const Vector4<T>& p_vector)
	{
		this = Multiply(p_vector);
		return *this;
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::Multiply(const Matrix4<T>& p_other)
	{
		Matrix4<T> previous(*this);

		elements[0] = ((previous.elements[0] * p_other.elements[0])
			+ (previous.elements[4] * p_other.elements[1])
			+ (previous.elements[8] * p_other.elements[2])
			+ (previous.elements[12] * p_other.elements[3]));
		elements[1] = ((previous.elements[1] * p_other.elements[0])
			+ (previous.elements[5] * p_other.elements[1])
			+ (previous.elements[9] * p_other.elements[2])
			+ (previous.elements[13] * p_other.elements[3]));
		elements[2] = ((previous.elements[2] * p_other.elements[0])
			+ (previous.elements[6] * p_other.elements[1])
			+ (previous.elements[10] * p_other.elements[2])
			+ (previous.elements[14] * p_other.elements[3]));
		elements[3] = ((previous.elements[3] * p_other.elements[0])
			+ (previous.elements[7] * p_other.elements[1])
			+ (previous.elements[11] * p_other.elements[2])
			+ (previous.elements[15] * p_other.elements[3]));

		elements[4] = ((previous.elements[0] * p_other.elements[4])
			+ (previous.elements[4] * p_other.elements[5])
			+ (previous.elements[8] * p_other.elements[6])
			+ (previous.elements[12] * p_other.elements[7]));
		elements[5] = ((previous.elements[1] * p_other.elements[4])
			+ (previous.elements[5] * p_other.elements[5])
			+ (previous.elements[9] * p_other.elements[6])
			+ (previous.elements[13] * p_other.elements[7]));
		elements[6] = ((previous.elements[2] * p_other.elements[4])
			+ (previous.elements[6] * p_other.elements[5])
			+ (previous.elements[10] * p_other.elements[6])
			+ (previous.elements[14] * p_other.elements[7]));
		elements[7] = ((previous.elements[3] * p_other.elements[4])
			+ (previous.elements[7] * p_other.elements[5])
			+ (previous.elements[11] * p_other.elements[6])
			+ (previous.elements[15] * p_other.elements[7]));

		elements[8] = ((previous.elements[0] * p_other.elements[8])
			+ (previous.elements[4] * p_other.elements[9])
			+ (previous.elements[8] * p_other.elements[10])
			+ (previous.elements[12] * p_other.elements[11]));
		elements[9] = ((previous.elements[1] * p_other.elements[8])
			+ (previous.elements[5] * p_other.elements[9])
			+ (previous.elements[9] * p_other.elements[10])
			+ (previous.elements[13] * p_other.elements[11]));
		elements[10] = ((previous.elements[2] * p_other.elements[8])
			+ (previous.elements[6] * p_other.elements[9])
			+ (previous.elements[10] * p_other.elements[10])
			+ (previous.elements[14] * p_other.elements[11]));
		elements[11] = ((previous.elements[3] * p_other.elements[8])
			+ (previous.elements[7] * p_other.elements[9])
			+ (previous.elements[11] * p_other.elements[10])
			+ (previous.elements[15] * p_other.elements[11]));

		elements[12] = ((previous.elements[0] * p_other.elements[12])
			+ (previous.elements[4] * p_other.elements[13])
			+ (previous.elements[8] * p_other.elements[14])
			+ (previous.elements[12] * p_other.elements[15]));
		elements[13] = ((previous.elements[1] * p_other.elements[12])
			+ (previous.elements[5] * p_other.elements[13])
			+ (previous.elements[9] * p_other.elements[14])
			+ (previous.elements[13] * p_other.elements[15]));
		elements[14] = ((previous.elements[2] * p_other.elements[12])
			+ (previous.elements[6] * p_other.elements[13])
			+ (previous.elements[10] * p_other.elements[14])
			+ (previous.elements[14] * p_other.elements[15]));
		elements[15] = ((previous.elements[3] * p_other.elements[12])
			+ (previous.elements[7] * p_other.elements[13])
			+ (previous.elements[11] * p_other.elements[14])
			+ (previous.elements[15] * p_other.elements[15]));

		return *this;
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::Multiply(const Matrix4<T>& p_left, const Matrix4<T>& p_right)
	{
		return Matrix4<T>(
			((p_left.elements[0] * p_right.elements[0])
				+ (p_left.elements[4] * p_right.elements[1])
				+ (p_left.elements[8] * p_right.elements[2])
				+ (p_left.elements[12] * p_right.elements[3])),
			((p_left.elements[1] * p_right.elements[0])
				+ (p_left.elements[5] * p_right.elements[1])
				+ (p_left.elements[9] * p_right.elements[2])
				+ (p_left.elements[13] * p_right.elements[3])),
			((p_left.elements[2] * p_right.elements[0])
				+ (p_left.elements[6] * p_right.elements[1])
				+ (p_left.elements[10] * p_right.elements[2])
				+ (p_left.elements[14] * p_right.elements[3])),
			((p_left.elements[3] * p_right.elements[0])
				+ (p_left.elements[7] * p_right.elements[1])
				+ (p_left.elements[11] * p_right.elements[2])
				+ (p_left.elements[15] * p_right.elements[3])),

			((p_left.elements[0] * p_right.elements[4])
				+ (p_left.elements[4] * p_right.elements[5])
				+ (p_left.elements[8] * p_right.elements[6])
				+ (p_left.elements[12] * p_right.elements[7])),
			((p_left.elements[1] * p_right.elements[4])
				+ (p_left.elements[5] * p_right.elements[5])
				+ (p_left.elements[9] * p_right.elements[6])
				+ (p_left.elements[13] * p_right.elements[7])),
			((p_left.elements[2] * p_right.elements[4])
				+ (p_left.elements[6] * p_right.elements[5])
				+ (p_left.elements[10] * p_right.elements[6])
				+ (p_left.elements[14] * p_right.elements[7])),
			((p_left.elements[3] * p_right.elements[4])
				+ (p_left.elements[7] * p_right.elements[5])
				+ (p_left.elements[11] * p_right.elements[6])
				+ (p_left.elements[15] * p_right.elements[7])),

			((p_left.elements[0] * p_right.elements[8])
				+ (p_left.elements[4] * p_right.elements[9])
				+ (p_left.elements[8] * p_right.elements[10])
				+ (p_left.elements[12] * p_right.elements[11])),
			((p_left.elements[1] * p_right.elements[8])
				+ (p_left.elements[5] * p_right.elements[9])
				+ (p_left.elements[9] * p_right.elements[10])
				+ (p_left.elements[13] * p_right.elements[11])),
			((p_left.elements[2] * p_right.elements[8])
				+ (p_left.elements[6] * p_right.elements[9])
				+ (p_left.elements[10] * p_right.elements[10])
				+ (p_left.elements[14] * p_right.elements[11])),
			((p_left.elements[3] * p_right.elements[8])
				+ (p_left.elements[7] * p_right.elements[9])
				+ (p_left.elements[11] * p_right.elements[10])
				+ (p_left.elements[15] * p_right.elements[11])),

			((p_left.elements[0] * p_right.elements[12])
				+ (p_left.elements[4] * p_right.elements[13])
				+ (p_left.elements[8] * p_right.elements[14])
				+ (p_left.elements[12] * p_right.elements[15])),
			((p_left.elements[1] * p_right.elements[12])
				+ (p_left.elements[5] * p_right.elements[13])
				+ (p_left.elements[9] * p_right.elements[14])
				+ (p_left.elements[13] * p_right.elements[15])),
			((p_left.elements[2] * p_right.elements[12])
				+ (p_left.elements[6] * p_right.elements[13])
				+ (p_left.elements[10] * p_right.elements[14])
				+ (p_left.elements[14] * p_right.elements[15])),
			((p_left.elements[3] * p_right.elements[12])
				+ (p_left.elements[7] * p_right.elements[13])
				+ (p_left.elements[11] * p_right.elements[14])
				+ (p_left.elements[15] * p_right.elements[15])));
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::operator*(const Matrix4<T>& p_other) const
	{
		return Multiply(*this, p_other);
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::operator*=(const Matrix4<T>& p_other)
	{
		return this->Multiply(p_other);
	}
#pragma endregion
#pragma region Division

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::Divide(T p_scalar)
	{
		if (p_scalar == 0)
			throw std::logic_error("Division by 0");

		for (T& element : elements)
			element /= p_scalar;
		return *this;
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::Divide(const Matrix4<T>& p_left, T p_scalar)
	{
		if (p_scalar == 0)
			throw std::logic_error("Division by 0");

		Matrix4<T> result(p_left);
		for (T& element : result.elements)
			element /= p_scalar;

		return result;
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::operator/(T p_scalar) const
	{
		return Divide(*this, p_scalar);
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::operator/=(T p_scalar)
	{
		return this->Divide(p_scalar);
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::Divide(const Matrix4<T>& p_other)
	{
		return (*this *= p_other.Inverse());
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::Divide(const Matrix4<T>& p_left, const Matrix4<T>& p_right)
	{
		Matrix4<T> leftCopy(p_left);
		return (leftCopy * p_right.Inverse());
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::operator/(const Matrix4<T>& p_other) const
	{
		return Divide(*this, p_other);
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::operator/=(const Matrix4<T>& p_other)
	{
		return this->Divide(p_other);
	}
#pragma endregion

#pragma endregion

#pragma region Matrix Operation

	template <typename T>
	constexpr bool Matrix4<T>::IsIdentity()
	{
		return memcmp(elements, Identity.elements, 16 * sizeof(T)) == 0;
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::Translation(const Vector3<T>& p_translation)
	{
		return Matrix4<T>(1, 0, 0, 0,
		                  0, 1, 0, 0,
		                  0, 0, 1, 0,
		                  p_translation.x, p_translation.y, p_translation.z, 1);
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::Translate(const Vector3<T>& p_translation)
	{
		return *this *= Matrix4<T>::Translation(p_translation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::Translate(const Matrix4<T>& p_matrix, const Vector3<T>& p_translation)
	{
		return p_matrix * Matrix4<T>::Translation(p_translation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotationOnAxisX(float p_rotation)
	{
		return Matrix4<T>(1, 0, 0, 0,
		                  0, MathTools::MathUtils::Cos(p_rotation), MathTools::MathUtils::Sin(p_rotation), 0,
		                  0, -MathTools::MathUtils::Sin(p_rotation), MathTools::MathUtils::Cos(p_rotation), 0,
		                  0, 0, 0, 1);
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::RotateOnAxisX(float p_rotation)
	{
		return *this *= Matrix4<T>::RotationOnAxisX(p_rotation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotateOnAxisX(const Matrix4<T>& p_matrix, float p_rotation)
	{
		return p_matrix * Matrix4<T>::RotationOnAxisX(p_rotation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotationOnAxisY(float p_rotation)
	{
		return Matrix4<T>(MathTools::MathUtils::Cos(p_rotation), 0, -MathTools::MathUtils::Sin(p_rotation), 0,
		                  0, 1, 0, 0,
		                  MathTools::MathUtils::Sin(p_rotation), 0, MathTools::MathUtils::Cos(p_rotation), 0,
		                  0, 0, 0, 1);
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::RotateOnAxisY(float p_rotation)
	{
		return *this *= Matrix4<T>::RotationOnAxisY(p_rotation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotateOnAxisY(const Matrix4<T>& p_matrix, float p_rotation)
	{
		return p_matrix * Matrix4<T>::RotationOnAxisY(p_rotation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotationOnAxisZ(float p_rotation)
	{
		return Matrix4<T>(MathTools::MathUtils::Cos(p_rotation), MathTools::MathUtils::Sin(p_rotation), 0, 0,
		                  -MathTools::MathUtils::Sin(p_rotation), MathTools::MathUtils::Cos(p_rotation), 0, 0,
		                  0, 0, 1, 0,
		                  0, 0, 0, 1);
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::RotateOnAxisZ(float p_rotation)
	{
		return *this *= Matrix4<T>::RotationOnAxisZ(p_rotation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotateOnAxisZ(const Matrix4<T>& p_matrix, float p_rotation)
	{
		return p_matrix * Matrix4<T>::RotationOnAxisZ(p_rotation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotationYXZ(float p_rotation)
	{
		return Matrix4<T>::RotationOnAxisY(p_rotation) *
			Matrix4<T>::RotationOnAxisX(p_rotation) *
			Matrix4<T>::RotationOnAxisZ(p_rotation);
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::RotateYXZ(float p_rotation)
	{
		return *this *= Matrix4<T>::RotationYXZ(p_rotation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotateYXZ(const Matrix4<T>& p_matrix, float p_rotation)
	{
		return p_matrix * Matrix4<T>::RotationYXZ(p_rotation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotationYXZ(const Vector3<T>& p_rotation)
	{
		return Matrix4<T>::RotationOnAxisY(p_rotation.y) *
			Matrix4<T>::RotationOnAxisX(p_rotation.x) *
			Matrix4<T>::RotationOnAxisZ(p_rotation.z);
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::RotateYXZ(const Vector3<T>& p_rotation)
	{
		return *this *= Matrix4<T>::RotationYXZ(p_rotation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::RotateYXZ(const Matrix4<T>& p_matrix, const Vector3<T>& p_rotation)
	{
		return p_matrix * Matrix4<T>::RotationYXZ(p_rotation);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::Scaling(const Vector3<T>& p_scale)
	{
		return Matrix4<T>(p_scale.x, 0, 0, 0,
		                  0, p_scale.y, 0, 0,
		                  0, 0, p_scale.z, 0,
		                  0, 0, 0, 1);
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::Scale(const Vector3<T>& p_scale)
	{
		return *this *= Matrix4<T>::Scaling(p_scale);
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::Scale(const Matrix4<T>& p_matrix, const Vector3<T>& p_scale)
	{
		return p_matrix * Matrix4<T>::Scaling(p_scale);
	}

	template <typename T>
	constexpr Matrix4<T>& Matrix4<T>::Transpose()
	{
		std::swap(elements[1], elements[4]);
		std::swap(elements[2], elements[8]);
		std::swap(elements[6], elements[9]);
		std::swap(elements[3], elements[12]);
		std::swap(elements[7], elements[13]);
		std::swap(elements[11], elements[14]);

		return *this;
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::Transpose(const Matrix4<T>& p_matrix)
	{
		return Matrix4<T>(p_matrix).Transpose();
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::Inverse() const
	{
		const float det = Determinant();

		if (fabs(det) <= MathTools::Generics::Epsilon)
			return Matrix4<T>::Identity;

		const float detInv = 1.0f / det;

		Matrix4<float> inverse;

		// Raw 1
		inverse.elements[0] = GetMinor(elements[5], elements[6], elements[7],
		                               elements[9], elements[10], elements[11],
		                               elements[13], elements[14], elements[15]) * detInv;
		inverse.elements[4] = GetMinor(elements[1], elements[2], elements[3],
		                               elements[9], elements[10], elements[11],
		                               elements[13], elements[14], elements[15]) * -detInv;
		inverse.elements[8] = GetMinor(elements[1], elements[2], elements[3],
		                               elements[5], elements[6], elements[7],
		                               elements[13], elements[14], elements[15]) * detInv;
		inverse.elements[12] = GetMinor(elements[1], elements[2], elements[3],
		                                elements[5], elements[6], elements[7],
		                                elements[9], elements[10], elements[11]) * -detInv;

		// Raw 2
		inverse.elements[1] = GetMinor(elements[4], elements[6], elements[7],
		                               elements[8], elements[10], elements[11],
		                               elements[12], elements[14], elements[15]) * detInv;
		inverse.elements[5] = GetMinor(elements[0], elements[2], elements[3],
		                               elements[8], elements[10], elements[11],
		                               elements[12], elements[14], elements[15]) * -detInv;
		inverse.elements[9] = GetMinor(elements[0], elements[2], elements[3],
		                               elements[4], elements[6], elements[7],
		                               elements[11], elements[14], elements[15]) * detInv;
		inverse.elements[13] = GetMinor(elements[0], elements[2], elements[3],
		                                elements[4], elements[6], elements[7],
		                                elements[8], elements[10], elements[11]) * -detInv;

		// Raw 3
		inverse.elements[2] = GetMinor(elements[4], elements[5], elements[7],
		                               elements[8], elements[9], elements[11],
		                               elements[12], elements[13], elements[15]) * detInv;
		inverse.elements[6] = GetMinor(elements[0], elements[1], elements[3],
		                               elements[8], elements[9], elements[11],
		                               elements[12], elements[13], elements[15]) * -detInv;
		inverse.elements[10] = GetMinor(elements[0], elements[1], elements[3],
		                                elements[4], elements[5], elements[7],
		                                elements[12], elements[13], elements[15]) * detInv;
		inverse.elements[14] = GetMinor(elements[0], elements[1], elements[3],
		                                elements[4], elements[5], elements[7],
		                                elements[8], elements[9], elements[11]) * -detInv;

		// Raw 4
		inverse.elements[3] = GetMinor(elements[4], elements[5], elements[6],
		                               elements[8], elements[9], elements[10],
		                               elements[12], elements[13], elements[14]) * detInv;
		inverse.elements[7] = GetMinor(elements[0], elements[1], elements[2],
		                               elements[8], elements[9], elements[10],
		                               elements[12], elements[13], elements[14]) * -detInv;
		inverse.elements[11] = GetMinor(elements[0], elements[1], elements[2],
		                                elements[4], elements[5], elements[6],
		                                elements[12], elements[13], elements[14]) * detInv;
		inverse.elements[15] = GetMinor(elements[0], elements[1], elements[2],
		                                elements[4], elements[5], elements[6],
		                                elements[8], elements[9], elements[10]) * -detInv;

		return inverse;
	}

	template <typename T>
	constexpr Matrix4<T> Matrix4<T>::Inverse(const Matrix4<T>& p_matrix)
	{
		return p_matrix.Inverse();
	}

	template <typename T>
	constexpr T Matrix4<T>::Determinant() const
	{
		return elements[0] * GetMinor(elements[5], elements[6], elements[7],
		                              elements[9], elements[10], elements[11],
		                              elements[13], elements[14], elements[15])
			- elements[4] * GetMinor(elements[1], elements[2], elements[3],
			                         elements[9], elements[10], elements[11],
			                         elements[13], elements[14], elements[15])
			+ elements[8] * GetMinor(elements[1], elements[2], elements[3],
			                         elements[5], elements[6], elements[7],
			                         elements[13], elements[14], elements[15])
			- elements[12] * GetMinor(elements[1], elements[2], elements[3],
			                          elements[5], elements[6], elements[7],
			                          elements[9], elements[10], elements[11]);
	}

	template <typename T>
	constexpr T Matrix4<T>::Determinant(const Matrix4<T>& p_matrix)
	{
		return p_matrix.Determinant();
	}

	template <typename T>
	constexpr float Matrix4<T>::GetMinor(float p_minor0, float p_minor1, float p_minor2, float p_minor3, float p_minor4,
	                           float p_minor5, float p_minor6, float p_minor7, float p_minor8)
	{
		return p_minor0 * (p_minor4 * p_minor8 - p_minor5 * p_minor7)
			- p_minor3 * (p_minor1 * p_minor8 - p_minor7 * p_minor2)
			+ p_minor6 * (p_minor1 * p_minor5 - p_minor4 * p_minor2);
	}

	template <typename T>
	constexpr Matrix4<float> Matrix4<T>::CreateView(float p_eyeX, float p_eyeY, float p_eyeZ,
	                                      float p_lookX, float p_lookY, float p_lookZ,
	                                      float p_upX, float p_upY, float p_upZ)
	{
		const Vector3<float> eye(p_eyeX, p_eyeY, p_eyeZ);
		const Vector3<float> look(p_lookX, p_lookY, p_lookZ);
		const Vector3<float> up(p_upX, p_upY, p_upZ);

		Vector3<float> forward(eye - look);
		forward.Normalize();

		Vector3<float> upXforward(up.CrossProduct(forward));
		upXforward.Normalize();

		const Vector3<float> v(forward.CrossProduct(upXforward));

		Matrix4<float> View;

		View.elements[0] = upXforward.x;
		View.elements[4] = upXforward.y;
		View.elements[8] = upXforward.z;
		View.elements[12] = -eye.DotProduct(upXforward);

		View.elements[1] = v.x;
		View.elements[5] = v.y;
		View.elements[9] = v.z;
		View.elements[13] = -eye.DotProduct(v);

		View.elements[2] = forward.x;
		View.elements[6] = forward.y;
		View.elements[10] = forward.z;
		View.elements[14] = -eye.DotProduct(forward);

		return View;
	}

	template <typename T>
	constexpr Matrix4<float> Matrix4<T>::CreateView(const Vector3<float>& p_eyes, const Vector3<float>& p_look,
		const Vector3<float>& p_up)
	{
		return CreateView(p_eyes.x, p_eyes.y, p_eyes.z, p_look.x, p_look.y, p_look.z, p_up.x, p_up.y, p_up.z);
	}

	template <typename T>
	constexpr Matrix4<float> Matrix4<T>::
	CreateView(Vector4<float> p_eyes, Vector4<float> p_look, Vector4<float> p_up)
	{
		p_eyes.Homogenize();
		p_look.Homogenize();
		p_up.Homogenize();
		return CreateView(p_eyes.x, p_eyes.y, p_eyes.z, p_look.x, p_look.y, p_look.z, p_up.x, p_up.y, p_up.z);
	}

	template <typename T>
	constexpr Matrix4<float> Matrix4<T>::CreateFrustum(float p_left, float p_right, float p_bottom,
	                                         float p_top, float p_zNear, float p_zFar)
	{
		const float maxView = 2.0f * p_zNear;
		const float width = p_right - p_left;
		const float height = p_top - p_bottom;
		const float zRange = p_zFar - p_zNear;

		if (width == 0)
			throw std::logic_error("Screen width is 0 : p_left == p_right");

		if (height == 0)
			throw std::logic_error("Screen height is 0 : p_bottom == p_top");

		if (height == 0)
			throw std::logic_error("View range is 0 : p_zNear == p_zFar");

		Matrix4<float> Frustum(0.f);

		Frustum.elements[0] = maxView / width;
		Frustum.elements[5] = maxView / height;
		Frustum.elements[8] = (p_right + p_left) / width;
		Frustum.elements[9] = (p_top + p_bottom) / height;
		Frustum.elements[10] = (-p_zFar - p_zNear) / zRange;
		Frustum.elements[11] = -1.0f;
		Frustum.elements[14] = (-maxView * p_zFar) / zRange;

		return Frustum;
	}

	template <typename T>
	constexpr Matrix4<float> Matrix4<T>::CreatePerspective(float p_fov, float p_aspectRatio, float p_zNear,
	                                             float p_zFar)
	{
		const float tangent = tanf((p_fov / 2.0f) * (MathTools::Generics::Pi / 180.0f));
		const float height = p_zNear * tangent;
		const float width = height * p_aspectRatio;
		return CreateFrustum(-width, width, -height, height, p_zNear, p_zFar);
	}

#pragma endregion

#pragma region Comparison & Conversion & Test

	template <typename T>
	constexpr T& Matrix4<T>::operator()(uint8_t p_row, uint8_t p_column)
	{
		if (p_row >= 4 || p_column >= 4)
			throw std::out_of_range(
				"Invalid index : " + std::to_string(p_row) + "," + std::to_string(p_column) + " is out of range");
		return elements[p_row + p_column * 4];
	}

	template <typename T>
	constexpr T Matrix4<T>::operator()(uint8_t p_row, uint8_t p_column) const
	{
		if (p_row >= 4 || p_column >= 4)
			throw std::out_of_range(
				"Invalid index : " + std::to_string(p_row) + "," + std::to_string(p_column) + " is out of range");
		return elements[p_row + p_column * 4];
	}

	template <typename T>
	constexpr Vector4<T> Matrix4<T>::GetRow(uint8_t p_row)
	{
		if (p_row >= 4)
			throw std::out_of_range("Invalid index : " + std::to_string(p_row) + " is out of range");

		return Vector4<T>(elements[p_row], elements[p_row + 4], elements[p_row + 8], elements[p_row + 12]);
	}

	template <typename T>
	constexpr Vector4<T> Matrix4<T>::GetColumn(uint8_t p_column)
	{
		if (p_column >= 4)
			throw std::out_of_range("Invalid index : " + std::to_string(p_column) + " is out of range");

		return Vector4<T>(elements[p_column * 4], elements[p_column * 4 + 1], elements[p_column * 4 + 2],
		                  elements[p_column * 4 + 3]);
	}

	template <typename T>
	constexpr std::string Matrix4<T>::ToString() const
	{
		return std::string(
			std::to_string(elements[0]) + "\t" + std::to_string(elements[4]) + "\t" + std::to_string(elements[8]) + "\t"
			+ std::to_string(elements[12]) + "\n" +

			std::to_string(elements[1]) + "\t" + std::to_string(elements[5]) + "\t" + std::to_string(elements[9]) + "\t"
			+ std::to_string(elements[13]) + "\n" +

			std::to_string(elements[2]) + "\t" + std::to_string(elements[6]) + "\t" + std::to_string(elements[10]) +
			"\t" + std::to_string(elements[14]) + "\n" +

			std::to_string(elements[3]) + "\t" + std::to_string(elements[7]) + "\t" + std::to_string(elements[11]) +
			"\t" + std::to_string(elements[15]));
	}

	template <typename T>
	constexpr std::string Matrix4<T>::ToString(const Matrix4<T>& p_matrix)
	{
		return p_matrix.ToString();
	}

	template <typename T>
	constexpr T* Matrix4<T>::ToArray()
	{
		return &elements[0];
	}

	template <typename T>
	constexpr T* Matrix4<T>::ToArray(Matrix4<T>& p_matrix)
	{
		return &p_matrix.elements[0];
	}

#pragma endregion

	template <typename T>
	std::ostream& operator<<(std::ostream& p_stream, const Matrix4<T>& p_matrix)
	{
		p_stream << p_matrix.elements[0] << "\t" << p_matrix.elements[4] << "\t" << p_matrix.elements[8] << "\t" <<
			p_matrix.elements[12] << "\n" <<

			p_matrix.elements[1] << "\t" << p_matrix.elements[5] << "\t" << p_matrix.elements[9] << "\t" <<
			p_matrix.elements[13] << "\n" <<

			p_matrix.elements[2] << "\t" << p_matrix.elements[6] << "\t" << p_matrix.elements[10] << "\t" <<
			p_matrix.elements[14] << "\n" <<

			p_matrix.elements[3] << "\t" << p_matrix.elements[7] << "\t" << p_matrix.elements[11] << "\t" <<
			p_matrix.elements[15] << "\n";

		return p_stream;
	}
}

#endif
