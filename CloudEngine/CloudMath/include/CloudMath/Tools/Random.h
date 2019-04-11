/**
* Project CloudMath
* @author CloudTech
* @version 1.0.0
*/

#pragma once
#ifndef _RANDOM_H
#define _RANDOM_H

#pragma warning(push)
#pragma warning(disable: 4251)

#include "CloudMath/stdafx.h"
#include "CloudMath/CloudMathAPI.h"

namespace CloudMath
{
	namespace MathTools
	{
		/**
		 * Provides some static random number generation
		 */
		class CLOUDMATH_API Random final
		{
		private:
			static std::default_random_engine s_generator;

		public:
			/* Desactivate the constructor (Un-instanciable static class) */
			Random() = delete;

			/**
			* Generate a random between two given integers (Closed interval)
			* @param p_min
			* @param p_max
			*/
			static int GenerateInt(int p_min, int p_max);

			/**
			* Generate a random between two given floats (Closed interval)
			* @param p_min
			* @param p_max
			*/
			static float GenerateFloat(float p_min, float p_max);

			/**
			 * Verify if the percentage is satisfied
			 * @param p_percentage
			 */
			static bool CheckPercentage(float p_percentage);
		};

	}
}

#pragma warning(pop)
#endif //_RANDOM_H