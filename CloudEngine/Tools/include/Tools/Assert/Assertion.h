#pragma once

#include "Tools/Logs/Log.h"

#define ADDBP __debugbreak()
#define ASSERTD(expression, message,...)	{if(!(expression)) { LOG(Log::Error(), "Assertion Failed : " << message); ADDBP;}}
