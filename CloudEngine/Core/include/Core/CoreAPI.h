#pragma once

#pragma warning(disable : 4251)					//Disable Compilation warning for not exporting internal classes

#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif
