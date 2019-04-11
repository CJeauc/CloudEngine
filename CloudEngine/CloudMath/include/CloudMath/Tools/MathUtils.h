/**
* Project CloudMath
* @author CloudTech
* @version 1.0.0
*/

#pragma once
#ifndef _UTILS_H
#define _UTILS_H

#include "CloudMath/CloudMathAPI.h"
#include "CloudMath/Tools/Generics.h"

namespace CloudMath
{
	namespace MathTools
	{
		/**
		* Utils class provides some simple mathematics tools, such as operations, pow, root, trigonometry stuffs...
		*/
		class CLOUDMATH_API MathUtils final
		{
		public:
			MathUtils() = delete;


			/**
			* Convert the given angle to radians
			* @param p_angle (In degrees)
			*/
			static constexpr float ToRadians(float p_angle)
			{
				return p_angle * CloudMath::MathTools::Generics::Pi * 0.00555555556f;
			}

			/**
			* Convert the given angle to degrees
			* @param p_angle (In radians)
			*/
			static constexpr float ToDegrees(float p_angle)
			{
				return p_angle * 180.0f / CloudMath::MathTools::Generics::Pi;
			}

			/**
			* Linearly interpolates between two values
			* @param p_a
			* @param p_b
			* @param p_alpha
			*/
			static constexpr float Lerp(float p_a, float p_b, float p_alpha)
			{
				return p_a + (p_b - p_a) * p_alpha;
			}

			/**
			* Return the pow of a numeric value with an integer exponent
			* @param p_value
			* @param p_exp
			*/
			template<typename T>
			static T Pow(T p_value, int p_exp);

			/**
			* Return the pow of a numeric value with a float exponent
			* @param p_value
			* @param p_exp
			*/
			template<typename T>
			static T Pow(T p_value, float p_exp);

			/**
			* Return the square root of a numeric value
			* @param p_value
			*/
			template<typename T>
			static T SquareRoot(T p_value);

			/**
			* Return the square root of a numeric value with float precision
			* @param p_value
			*/
			template<typename T>
			static T SquareRootF(T p_value);

			/**
			* Return the root of a numeric value
			* @param p_value
			* @param p_nRoot
			*/
			template<typename T>
			static T Root(T p_value, float p_nRoot);

			/**
			* Return the greatest common divider of the two given integers
			* @param p_a
			* @param p_b
			*/
			static int GreatestCommonDivider(int p_a, int p_b);

			/**
			* Return the smallest common divider of the two given integers
			* @param p_a
			* @param p_b
			*/
			static int LeastCommonMultiple(int p_a, int p_b);

			/**
			* Return the decimal part of a float as an integer
			* @param p_value
			*/
			static constexpr float GetDecimalPart(float p_value);

			/**
			* Return the absolute value of a numeric value
			* @param p_value
			*/
			template<typename T>
			static T Abs(T p_value);

			/**
			* Mathematic sinus implementation
			* @param p_value
			*/
			static float Sin(float p_value);

			/**
			* Mathematic sinus implementation with float precision
			* @param p_value
			*/
			static float SinF(float p_value);

			/**
			* Mathematic cosinus implementation
			* @param p_value
			*/
			static float Cos(float p_value);

			/**
			* Mathematic cosinus implementation with float precision
			* @param p_value
			*/
			static float CosF(float p_value);

			/**
			* Mathematic tangente implementation
			* @param p_value
			*/
			static float Tan(float p_value);

			/**
			* Mathematic arc cosinus implementation
			* @param p_value
			*/
			static float Arccos(float p_value);

			/**
			* Mathematic arc sinus implementation
			* @param p_value
			*/
			static float Arcsin(float p_value);

			/**
			* Mathematic arc tangente implementation
			* @param p_value
			*/
			static float Arctan(float p_value);

			/**
			* Mathematic arc tangente implementation
			* @param p_valueYx
			* @param p_valueXx
			*/
			static float Arctan2(float p_valueYx, float p_valueXx);

			/*
			* Return 0 if value is smaller than 0
			* @param p_value
			*/
			static float ToZeroIfSmaller(float p_value);

			/*
			* Return 0 if value is to close to 0
			* @param p_value
			*/
			static float RoundToZeroIfToSmall(float p_value);
		};
	}
}

#include "MathUtils.inl"

#endif //_UTILS_H