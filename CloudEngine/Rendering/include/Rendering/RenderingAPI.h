#pragma once

#pragma warning(disable : 4251)					//Disable Compilation warning for not exporting internal classes

#ifdef RENDERING_EXPORTS
#define RENDERING_API __declspec(dllexport)
#else
#define RENDERING_API __declspec(dllimport)
#endif