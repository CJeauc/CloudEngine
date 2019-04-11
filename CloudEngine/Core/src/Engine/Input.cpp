#include "Core/stdafx.h"
#include "Core/Engine/Input.h"
#include "Core/Engine/CloudEngine.h"

using namespace Core;

#pragma warning(push)
#pragma warning(disable: 4244)

std::unordered_map<Key, bool> Input::m_keyStates;
std::unordered_map<Key, bool> Input::m_keyEvents;
bool Input::m_firstMouse	= true; 
float Input::m_mouseLastX	= 0;
float Input::m_mouseLastY   = 0;
float Input::m_mouseXOffset = 0;
float Input::m_mouseYOffset = 0;
float Input::m_sensitivity	= 0.1f;
bool Input::m_mouseButtonRight = false;
bool Input::m_mouseButtonLeft = false;
bool Input::m_updateMouse = false;
bool Input::m_Qt = false;

void Input::KeyCallBack(GLFWwindow* p_window, int p_key, int p_scanCode, int p_action, int p_mods)
{
	Key key = static_cast<Key>(p_key);

	if (p_action == GLFW_PRESS)
	{
		m_keyEvents[key] = true;
		m_keyStates[key] = true;
	}
	else if (p_action == GLFW_RELEASE)
	{
		m_keyEvents[key] = false;
		m_keyStates[key] = false;
	}
}

void Input::MouseCallBack(GLFWwindow* p_window, double p_xPos, double p_yPos)
{
	if (!m_Qt)
	{
		//m_updateMouse = true;
		if (m_firstMouse)
		{
			m_mouseLastX = p_xPos;
			m_mouseLastY = p_yPos;
			m_firstMouse = false;
		}

		double temp = 1; // Core::CloudEngine::DeltaTime;
		m_mouseXOffset = (p_xPos - m_mouseLastX) * temp;
		m_mouseYOffset = (m_mouseLastY - p_yPos) * temp;			//Y inverted

		m_mouseLastX = p_xPos;
		m_mouseLastY = p_yPos;

		/*SLOG(Log::Info(), "X: " << m_mouseLastX << " Y: " << m_mouseLastY );*/
	}
}

void Input::MouseButtonCallBack(GLFWwindow* p_window, int p_button, int p_action, int p_mods)
{
	if (p_button == GLFW_MOUSE_BUTTON_RIGHT && p_action == GLFW_PRESS)
		m_mouseButtonRight = true;

	if (p_button == GLFW_MOUSE_BUTTON_LEFT && p_action == GLFW_PRESS)
		m_mouseButtonLeft = true;
}

bool Input::GetKey(Key p_key)
{
	return m_keyStates.find(p_key) != m_keyStates.end() && m_keyStates[p_key];
}

bool Input::GetKeyDown(Key p_key)
{
	return m_keyEvents.find(p_key) != m_keyEvents.end() && m_keyEvents[p_key];
}

bool Input::GetKeyUp(Key p_key)
{
	return m_keyEvents.find(p_key) != m_keyEvents.end() && !m_keyEvents[p_key];
}

float Input::MouseX()
{
	return static_cast<float>(m_mouseLastX);
}

float Input::MouseY()
{
	return static_cast<float>(m_mouseLastY);
}

float Input::MouseXOffset()
{
	return static_cast<float>(m_mouseXOffset);
}

float Input::MouseYOffset()
{
	return static_cast<float>(m_mouseYOffset);
}

bool Input::MouseButton(unsigned int p_button)
{
	if(p_button == 0)
		return m_mouseButtonLeft;
	if (p_button == 1)
		return m_mouseButtonRight;

	return false;
}

void Input::Process()
{
	Clear();
	glfwPollEvents();
}

void Core::Input::SetMouseUpdate(bool p_shouldMouseUpdate)
{
	m_updateMouse = p_shouldMouseUpdate;
}

void Input::SetLastPos(double p_xPos, double p_yPos)
{
	m_mouseLastX = p_xPos;
	m_mouseLastY = p_yPos;
}

void Input::SetSensitivity(float p_sensitivity)
{
	m_sensitivity = p_sensitivity;
}

void Input::ResetMouse()
{
	m_firstMouse = true;
}

void Core::Input::SetMouseX(float p_mouseX)
{
	m_mouseLastX = p_mouseX;
}

void Core::Input::SetMouseY(float p_mouseY)
{
	m_mouseLastY = p_mouseY;
}

void Input::Clear()
{
	m_keyEvents.clear();
	m_mouseButtonRight = false;
	m_mouseButtonLeft = false;
	m_mouseXOffset = 0;
	m_mouseYOffset = 0;
}

#pragma warning(pop)