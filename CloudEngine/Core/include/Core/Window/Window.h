#pragma once

#include "Core/stdafx.h"
#include "Core/CoreAPI.h"
#include "Core/Engine/Input.h"
#include "Rendering/Driver/Driver.h"

namespace Core
{
	class CORE_API Window
	{
	public:
		Window() = delete;
		Window(const int& p_width, const int& p_height);
		~Window();

		bool Create();

		bool ShouldClose();
		void SwapBuffers();

		static void SetFramebufferSizeCallback(GLFWwindow* p_window, int p_width, int p_height);

		int Width() const;
		int Height() const;
		float AspectRatio() const;

		GLFWwindow* GLFWWindow() const;

		/* !!!!!!!!!!!!!!!!!! */
		Rendering::Driver* m_driver;

	private:
		static int m_width;
		static int m_height;
		GLFWwindow* m_window;
	};
}