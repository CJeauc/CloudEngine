#pragma once

#include "Core/stdafx.h"
#include "Core/CoreAPI.h"
#include "Core/Window/Window.h"
#include "Core/Engine/Key.h"
#include "Rendering.h"

namespace Core
{
	class CORE_API Input
	{
	public:
		static void KeyCallBack(GLFWwindow* p_window, int p_key, int p_scanCode, int p_action, int p_mods);
		static void MouseCallBack(GLFWwindow* p_window, double p_xPos, double p_yPos);
		static void MouseButtonCallBack(GLFWwindow* p_window, int p_button, int p_action, int p_mods);
		static bool GetKey(Key p_key);		//This is the state of the key
		static bool GetKeyDown(Key p_key);	//This is the event on the key: pressed, released
		static bool GetKeyUp(Key p_key);

		static float MouseX();
		static float MouseY();
		static float MouseXOffset();
		static float MouseYOffset();
		static bool MouseButton(unsigned int p_button);


		static void Process();
		static void SetMouseUpdate(bool p_shouldMouseUpdate);
		static bool ShouldUpdateMouse() { return m_updateMouse; };
		static void SetLastPos(double p_xPos, double p_yPos);
		static void SetSensitivity(float p_sensitivity);
		static void ResetMouse();

		static void SetMouseX(float p_mouseX);
		static void SetMouseY(float p_mouseY);

		static void SetQt()
		{
			m_Qt = true;
		}

		static void Clear();
		

	private:
		static std::unordered_map<Key, bool> m_keyStates;
		static std::unordered_map<Key, bool> m_keyEvents;

		/*Mouse Stuff*/
		static bool m_updateMouse;
		static bool m_firstMouse;
		static float m_sensitivity; 

		static bool m_mouseButtonRight;
		static bool m_mouseButtonLeft;
		static bool m_Qt;

	public :
		static float m_mouseLastX;
		static float m_mouseLastY;

		static float m_mouseXOffset;
		static float m_mouseYOffset;
	};
}
