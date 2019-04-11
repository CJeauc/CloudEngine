#pragma once

#include "Tools/stdafx.h"

template<typename T>
std::string GetNameFromType()
{
	const std::string name = typeid(T).name();
	return name.substr(name.find_last_of("::") + 1);
}