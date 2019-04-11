/**
 * Project AltMath
 * @author GP2021
 * @version 1.0.0
 */

#include "CloudMath/stdafx.h"
#include "CloudMath/Tools/Random.h"

std::default_random_engine CloudMath::MathTools::Random::s_generator = std::default_random_engine(static_cast<unsigned int>(time(0)));

int CloudMath::MathTools::Random::GenerateInt(int p_min, int p_max)
{
	if (p_min > p_max)
		throw std::logic_error("Min is superior than max");

	return std::uniform_int_distribution<int>(p_min, p_max)(s_generator);
}

float CloudMath::MathTools::Random::GenerateFloat(float p_min, float p_max)
{
	if (p_min > p_max)
		throw std::logic_error("Min is superior than max");

	return std::uniform_real_distribution<float>(p_min, p_max)(s_generator);
}

bool CloudMath::MathTools::Random::CheckPercentage(float p_percentage)
{
	return std::uniform_real_distribution<float>(0.f, 100.f)(s_generator) <= p_percentage;
}
