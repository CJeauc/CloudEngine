#include "stdafx.h"
#include "LightComponentGUI.h"

using namespace QtEditor;

LightComponentGUI::LightComponentGUI(const std::string& p_name, QWidget* p_parent)
	: AComponentGUI(p_name, p_parent)
{
}

LightComponentGUI::~LightComponentGUI()
{
}


void LightComponentGUI::SetupFrame()
{
}

void LightComponentGUI::BindComponent(std::shared_ptr<Core::AComponent> p_component)
{
}
