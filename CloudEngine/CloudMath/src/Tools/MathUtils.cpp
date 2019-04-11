/**
 * Project AltMath
 * @author GP2021
 * @version 1.0.0
 */

#include "CloudMath/stdafx.h"
#include "CloudMath/Tools/MathUtils.h"

int CloudMath::MathTools::MathUtils::GreatestCommonDivider(int p_a, int p_b)
{
    // Modulo then swap a and b
	while (p_b)
		p_b ^= p_a ^= p_b ^= p_a %= p_b;

	return p_a;
}

int CloudMath::MathTools::MathUtils::LeastCommonMultiple(int p_a, int p_b)
{
	return p_a * p_b / GreatestCommonDivider(p_a, p_b);
}

constexpr float CloudMath::MathTools::MathUtils::GetDecimalPart(float p_value)
{
    return p_value - static_cast<int>(p_value);
}

float CloudMath::MathTools::MathUtils::Sin(float p_value)
{
	return std::sin(p_value);
}

float CloudMath::MathTools::MathUtils::SinF(float p_value)
{
	return std::sinf(p_value);
}

float CloudMath::MathTools::MathUtils::Cos(float p_value)
{
	return std::cos(p_value);
}

float CloudMath::MathTools::MathUtils::CosF(float p_value)
{
	return std::cosf(p_value);
}

float CloudMath::MathTools::MathUtils::Tan(float p_value)
{
	return std::tan(p_value);
}

float CloudMath::MathTools::MathUtils::Arccos(float p_value)
{
	return std::acos(p_value);
}

float CloudMath::MathTools::MathUtils::Arcsin(float p_value)
{
	return std::asin(p_value);
}

float CloudMath::MathTools::MathUtils::Arctan(float p_value)
{
	return std::atan(p_value);
}

float CloudMath::MathTools::MathUtils::Arctan2(float p_valueYx, float p_valueXx)
{
	return std::atan2(p_valueYx, p_valueXx);
}

float CloudMath::MathTools::MathUtils::ToZeroIfSmaller(float p_value)
{
	return p_value >= Generics::Epsilon ? p_value : 0;
}

float CloudMath::MathTools::MathUtils::RoundToZeroIfToSmall(float p_value)
{
	return abs(p_value) >= Generics::Epsilon ? p_value : 0;
}
