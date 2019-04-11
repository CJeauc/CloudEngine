/**
* Project CloudMath
* @author CloudTech
* @version 1.0.0
*/

#pragma once
#ifndef _UTILS_INL
#define _UTILS_INL

#include "CloudMath/Tools/MathUtils.h"

template<typename T>
T CloudMath::MathTools::MathUtils::Pow(T p_value, int p_exp)
{
	static_assert(std::is_arithmetic<T>::value, "The value to pow must be arithmetic");
	return static_cast<T>(std::pow(p_value, p_exp));
}

template<typename T>
T CloudMath::MathTools::MathUtils::Pow(T p_value, float p_exp)
{
	static_assert(std::is_arithmetic<T>::value, "The value to pow must be arithmetic");
	return static_cast<T>(std::pow(p_value, p_exp));
}

template <typename T>
T CloudMath::MathTools::MathUtils::SquareRoot(T p_value)
{
	static_assert(std::is_arithmetic<T>::value, "The value to root must be arithmetic");
	return static_cast<T>(std::sqrt(p_value));
}

template <typename T>
T CloudMath::MathTools::MathUtils::SquareRootF(T p_value)
{
	static_assert(std::is_arithmetic<T>::value, "The value to root must be arithmetic");
	return static_cast<T>(std::sqrtf(p_value));
}

template<typename T>
T CloudMath::MathTools::MathUtils::Root(T p_value, float p_nRoot)
{
	static_assert(std::is_arithmetic<T>::value, "The value to root must be arithmetic");
	return static_cast<T>(std::pow(p_value, 1 / p_nRoot));
}

template<typename T>
T CloudMath::MathTools::MathUtils::Abs(T p_value)
{
	static_assert(std::is_arithmetic<T>::value, "The value to Abs must be arithmetic");
	return static_cast<T>(std::abs(p_value));
}

#endif // _UTILS_INL
