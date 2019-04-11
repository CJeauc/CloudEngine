#include "Rendering/stdafx.h"
#include "Tools.h"
#include "Rendering/Driver/Driver.h"

using namespace Rendering;

Driver::Driver()
{
}

bool Rendering::Driver::Load(GLADloadproc p_gladLoadProc)
{
	if (!gladLoadGLLoader(p_gladLoadProc))
		return false;

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_MULTISAMPLE);

	SLOG(Log::Info(), "Driver Initialized");

	DisplayDriverInfo();

	return true;
}

void Driver::DisplayDriverInfo()
{
	SLOG(Log::Info(), "Driver Info");

	SLOG(Log::Info(), glGetString(GL_VERSION));
	SLOG(Log::Info(), glGetString(GL_VENDOR));
	SLOG(Log::Info(), glGetString(GL_RENDERER));
	SLOG(Log::Info(), glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void Driver::SetViewport(int p_width, int p_height)
{
	glViewport(0, 0, p_width, p_height);
}