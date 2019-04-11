#include "Core/stdafx.h"
#include "Tools.h"
#include "Core/Window/Window.h"
#include "Rendering/Driver/Driver.h"
#include <Core/CoreComponent/UniformRendering.h>

using namespace Core;

int Window::m_width = 0;
int Window::m_height = 0;

Window::Window(const int& p_width, const int& p_height)
{
	m_width = p_width;
	m_height = p_height;
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool Window::Create()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	m_window = glfwCreateWindow(m_width, m_height, "Cloud Engine", nullptr, nullptr);

	if (!m_window)
	{
		glfwTerminate();
		return false;
	}

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(m_window, &screenWidth, &screenHeight);
	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, Window::SetFramebufferSizeCallback);

	/*Locking The Cursor*/
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//vSync off set 1 to cap at 60
	glfwSwapInterval(0);

	SLOG(Log::Info(), "Window initialized");
	
	return true;
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

void Window::SetFramebufferSizeCallback(GLFWwindow* window, int p_width, int p_height)
{
	m_width = p_width;
	m_height = p_height;

	Rendering::Driver::SetViewport(m_width, m_height);
	//Uniform rendering Projection
	Core::Components::UniformRendering::SetProjectionAspect(static_cast<float>(p_width) / static_cast<float>(p_height));
}

int Window::Width() const
{
	return m_width;
}

int Window::Height() const
{
	return m_height;
}

float Window::AspectRatio() const
{
	return static_cast<float>(m_width) / m_height;
}

GLFWwindow* Window::GLFWWindow() const
{
	return m_window;
}