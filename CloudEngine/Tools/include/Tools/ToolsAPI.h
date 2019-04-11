#pragma once

#pragma warning(disable : 4251)					//Disable Compilation warning for not exporting internal classes

#ifdef TOOLS_EXPORTS
#define TOOLS_API __declspec(dllexport)
#else
#define TOOLS_API __declspec(dllimport)
#endif