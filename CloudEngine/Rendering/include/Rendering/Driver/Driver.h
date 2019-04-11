#pragma once

#include "Rendering/RenderingAPI.h"

namespace Rendering
{
	class RENDERING_API Driver
	{
	public:
		Driver();
		~Driver() = default;

		bool Load(GLADloadproc p_gladLoadProc);
		void DisplayDriverInfo();

		static void SetViewport(int p_width, int p_height);

		//This can have methods to set different options for openGL
	};
}