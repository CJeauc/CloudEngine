#pragma once

#include <Core/Engine/CloudEngine.h>

namespace QtEditor
{
	class KeyMapper
	{
	public:
		static int ToEngineInput(int p_qtKey);
	};
}
