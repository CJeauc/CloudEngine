#pragma once

#pragma warning(disable : 4251)					//Disable Compilation warning for not exporting internal classes

#ifdef CLOUDMATH_EXPORTS
#define CLOUDMATH_API __declspec(dllexport)
#else
#define CLOUDMATH_API __declspec(dllimport)
#endif