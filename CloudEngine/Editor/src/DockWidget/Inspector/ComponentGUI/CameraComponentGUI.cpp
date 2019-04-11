#include "stdafx.h"
#include "CameraComponentGUI.h"

using namespace QtEditor;

CameraComponentGUI::CameraComponentGUI(const std::string& p_name, QWidget* p_parent)
	: AComponentGUI(p_name, p_parent)
{
}

CameraComponentGUI::~CameraComponentGUI()
{
}


void CameraComponentGUI::SetupFrame()
{
}

void CameraComponentGUI::BindComponent(std::shared_ptr<Core::AComponent> p_component)
{
}
