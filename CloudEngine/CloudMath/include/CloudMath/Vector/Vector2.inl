/**
* Project CloudMath
* @author CloudTech
* @version 1.0.0
*/

#pragma once
#ifndef _VECTOR2_INL
#define _VECTOR2_INL

#include "CloudMath/Tools/MathUtils.h"

namespace CloudMath
{
	template <typename T>
	constexpr Vector2<T> Vector2<T>::Zero() { return Vector2<float>(0, 0); }

#pragma region Constructors & Assignment

	template <typename T>
	constexpr Vector2<T>::Vector2()
		: x(0), y(0) {}

	template <typename T>
	constexpr Vector2<T>::Vector2(T p_x, T p_y)
		: x(p_x), y(p_y) {}

	template <typename T>
	constexpr Vector2<T>::Vector2(const Vector2<T>& p_other)
		: x(p_other.x), y(p_other.y) { }

	template <typename T>
	constexpr Vector2<T>::Vector2(Vector2<T>&& p_other) noexcept
		: x{std::move(p_other.x)}, y{std::move(p_other.y)} { }

	template <typename T>
	constexpr Vector2<T>& Vector2<T>::operator=(const Vector2<T>& p_other)
	{
		x = p_other.x;
		y = p_other.y;

		return *this;
	}

	template <typename T>
	constexpr Vector2<T>& Vector2<T>::operator=(Vector2<T>&& p_other) noexcept
	{
		x = std::move(p_other.x);
		y = std::move(p_other.y);

		return *this;
	}

#pragma endregion
#pragma region Tests & Comparisons

	template <typename T>
	constexpr bool Vector2<T>::IsParallelTo(const Vector2<T>& p_other) const
	{
		Vector2<T> normThis = Vector2<T>::Normalize(*this);
		Vector2<T> normOther = Vector2<T>::Normalize(p_other);
		return (normThis == normOther || normThis == (normOther * -1));
	}

	template <typename T>
	constexpr bool Vector2<T>::AreParallel(const Vector2<T>& p_left, const Vector2<T>& p_right)
	{
		return p_left.IsParallelTo(p_right);
	}

	template <typename T>
	constexpr bool Vector2<T>::IsPerpendicularTo(const Vector2<T>& p_other) const
	{
		return DotProduct(p_other) == 0;
	}

	template <typename T>
	constexpr bool Vector2<T>::ArePerpendicular(const Vector2<T>& p_left, const Vector2<T>& p_right)
	{
		return p_left.IsPerpendicularTo(p_right);
	}

	template <typename T>
	constexpr bool Vector2<T>::IsEqualTo(const Vector2<T>& p_other) const
	{
		return (x == p_other.x && y == p_other.y);
	}

	template <typename T>
	constexpr bool Vector2<T>::AreEqual(const Vector2<T>& p_left, const Vector2<T>& p_right)
	{
		return p_left.IsEqualTo(p_right);
	}

	template <typename T>
	constexpr bool Vector2<T>::operator==(const Vector2<T>& p_other) const
	{
		return IsEqualTo(p_other);
	}

#pragma endregion
#pragma region Arithmetic Operations

#pragma region Add

	template <typename T>
	Vector2<T>& Vector2<T>::Add(T p_scalar)
	{
		x += p_scalar;
		y += p_scalar;

		return *this;
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::Add(const Vector2<T>& p_left, T p_scalar)
	{
		return Vector2<T>(p_left).Add(p_scalar);
	}

	template <typename T>
	Vector2<T>& Vector2<T>::Add(const Vector2<T>& p_other)
	{
		x += p_other.x;
		y += p_other.y;

		return *this;
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::Add(const Vector2<T>& p_left, const Vector2<T>& p_right)
	{
		return Vector2<T>(p_left).Add(p_right);
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::operator+(T p_scalar) const
	{
		return Vector2<T>(*this).Add(p_scalar);
	}

	template <typename T>
	Vector2<T>& Vector2<T>::operator+=(T p_scalar)
	{
		return Add(p_scalar);
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::operator+(const Vector2<T>& p_other) const
	{
		return Vector2<T>(*this).Add(p_other);
	}

	template <typename T>
	Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& p_other)
	{
		return Add(p_other);
	}

#pragma endregion
#pragma region Subtract

	template <typename T>
	Vector2<T>& Vector2<T>::Subtract(T p_scalar)
	{
		x -= p_scalar;
		y -= p_scalar;

		return *this;
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::Subtract(const Vector2<T>& p_left, T p_scalar)
	{
		return Vector2<T>(p_left).Subtract(p_scalar);
	}

	template <typename T>
	Vector2<T>& Vector2<T>::Subtract(const Vector2<T>& p_other)
	{
		x -= p_other.x;
		y -= p_other.y;

		return *this;
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::Subtract(const Vector2<T>& p_left, const Vector2<T>& p_right)
	{
		return Vector2<T>(p_left).Subtract(p_right);
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::operator-(T p_scalar) const
	{
		return Vector2<T>(*this).Subtract(p_scalar);
	}

	template <typename T>
	Vector2<T>& Vector2<T>::operator-=(T p_scalar)
	{
		return Subtract(p_scalar);
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::operator-(const Vector2<T>& p_other) const
	{
		return Vector2<T>(*this).Subtract(p_other);
	}

	template <typename T>
	Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& p_other)
	{
		return Subtract(p_other);
	}

#pragma endregion
#pragma region Multiply

	template <typename T>
	Vector2<T>& Vector2<T>::Multiply(T p_scalar)
	{
		x *= p_scalar;
		y *= p_scalar;

		return *this;
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::Multiply(const Vector2<T>& p_left, T p_scalar)
	{
		return Vector2<T>(p_left).Multiply(p_scalar);
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::operator*(T p_scalar) const
	{
		return Vector2<T>(*this).Multiply(p_scalar);
	}

	template <typename T>
	Vector2<T>& Vector2<T>::operator*=(T p_scalar)
	{
		return Multiply(p_scalar);
	}

#pragma endregion
#pragma region Divide

	template <typename T>
	Vector2<T>& Vector2<T>::Divide(T p_scalar)
	{
		if (p_scalar == 0)
			throw std::logic_error("Division by 0");

		x /= p_scalar;
		y /= p_scalar;

		return *this;
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::Divide(const Vector2<T>& p_left, T p_scalar)
	{
		return Vector2<T>(p_left).Divide(p_scalar);
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::operator/(T p_scalar) const
	{
		return Vector2<T>(*this).Divide(p_scalar);
	}

	template <typename T>
	Vector2<T>& Vector2<T>::operator/=(T p_scalar)
	{
		return Divide(p_scalar);
	}

#pragma endregion

#pragma endregion
#pragma region Vector Operations

	template <typename T>
	constexpr T Vector2<T>::Length() const
	{
		return (static_cast<T>(MathTools::MathUtils::SquareRootF(x * x + y * y)));
	}

	template <typename T>
	constexpr T Vector2<T>::Length(const Vector2<T>& p_vector)
	{
		return p_vector.Length();
	}

	template <typename T>
	constexpr T Vector2<T>::LengthSquare() const
	{
		return (static_cast<T>(x * x + y * y));
	}

	template <typename T>
	constexpr T Vector2<T>::LengthSquare(const Vector2<T>& p_vector)
	{
		return p_vector.LengthSquare();
	}

	template <typename T>
	constexpr T Vector2<T>::DotProduct(const Vector2<T>& p_other) const
	{
		return x * p_other.x + y * p_other.y;
	}

	template <typename T>
	constexpr T Vector2<T>::DotProduct(const Vector2<T>& p_left, const Vector2<T>& p_right)
	{
		return p_left.DotProduct(p_right);
	}

	template <typename T>
	constexpr T Vector2<T>::AngleBetween(const Vector2<T>& p_other) const
	{
		float dotProduct = DotProduct(p_other);
		T lengthProduct = Length() * p_other.Length();

		if (lengthProduct > 0)
		{
			T fractionResult = dotProduct / lengthProduct;

			if (fractionResult >= -1 && fractionResult <= 1)
				return (static_cast<T>(MathTools::MathUtils::Arccos(fractionResult)));
		}

		return 0;
	}

	template <typename T>
	constexpr T Vector2<T>::AngleBetween(const Vector2<T>& p_left, const Vector2<T>& p_right)
	{
		return p_left.AngleBetween(p_right);
	}

	template <typename T>
	Vector2<T>& Vector2<T>::Normalize()
	{
		const float length = Length();
		if (length > 0 && length != 1)
		{
			x /= length;
			y /= length;
		}

		return *this;
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::Normalize(const Vector2<T>& p_vector)
	{
		return Vector2<T>(p_vector).Normalize();
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::Lerp(const Vector2<T>& p_start, const Vector2<T>& p_end,
	                                      float p_interpolationCoefficient)
	{
		if (p_interpolationCoefficient >= 0 && p_interpolationCoefficient <= 1)
			return (p_start + (p_end - p_start) * p_interpolationCoefficient);

		return p_start;
	}

	template <typename T>
	constexpr Vector2<T> Vector2<T>::Slerp(const Vector2<T>& p_start, const Vector2<T>& p_end,
	                                       float p_interpolationCoefficient)
	{
		if (p_interpolationCoefficient >= 0 && p_interpolationCoefficient <= 1)
		{
			//float theta = Mathf.Acos(dot)*percent;
			const float angle = p_start.AngleBetween(p_end) * p_interpolationCoefficient;
			Vector2<T> relativeVector = p_end - p_start * p_start.DotProduct(p_end);
			relativeVector.Normalize();

			return (p_start * MathTools::MathUtils::Cos(angle) + relativeVector * MathTools::MathUtils::Sin(angle));
		}

		return p_start;
	}

#pragma endregion
#pragma region Conversions

	template <typename T>
	constexpr std::string Vector2<T>::ToString() const
	{
		return std::string("x : " + std::to_string(x) + " y : " + std::to_string(y));
	}

#pragma endregion
#pragma region Outside Operators

	template <typename T>
	constexpr std::ostream& operator<<(std::ostream& p_stream, const CloudMath::Vector2<T>& p_vector)
	{
		p_stream << p_vector.ToString();
		return p_stream;
	}

	template <typename T>
	constexpr Vector2<T> operator+(T p_scalar, const Vector2<T>& p_vector)
	{
		return p_vector + p_scalar;
	}

	template <typename T>
	constexpr Vector2<T> operator*(T p_scalar, const Vector2<T>& p_vector)
	{
		return p_vector * p_scalar;
	}

#pragma endregion
}

#endif //_VECTOR2_INL
