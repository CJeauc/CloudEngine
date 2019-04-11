#pragma once

#pragma once

#pragma warning(disable : 4251)					//Disable Compilation warning for not exporting internal classes

#ifdef PHYSIC_EXPORTS
#define PHYSIC_API __declspec(dllexport)
#else
#define PHYSIC_API __declspec(dllimport)
#endif