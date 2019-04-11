#include "stdafx.h"
#include "MaterialComponentGUI.h"

using  namespace QtEditor;

MaterialComponentGUI::MaterialComponentGUI(const std::string& p_name, QWidget* p_parent)
	:AComponentGUI(p_name, p_parent)
{
}

MaterialComponentGUI::~MaterialComponentGUI()
{
}


void MaterialComponentGUI::SetupFrame()
{
}

void MaterialComponentGUI::BindComponent(std::shared_ptr<Core::AComponent> p_component)
{
}
