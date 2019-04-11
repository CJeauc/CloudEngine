/**
* Project CloudMath
* @author CloudTech
* @version 1.0.0
*/

#pragma once
#ifndef _GENERICS_H
#define _GENERICS_H

#include "CloudMath/CloudMathAPI.h"

namespace CloudMath
{
	namespace MathTools
	{
		/**
		 * This class exposes some constant variables to the user
		 */
		struct CLOUDMATH_API Generics final
		{
			static const float	Pi;
			static const float	E;
			static const float Epsilon;

			/* Desactivate the constructor (Un-instanciable static class) */
			Generics() = delete;
		};
	}
}

#endif //_GENERICS_H