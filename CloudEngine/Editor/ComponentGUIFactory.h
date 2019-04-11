#pragma once
#include "AComponentGUI.h"
#include "Core/ECS/Component/Component.h"

namespace QtEditor
{
	class ComponentGUIFactory
	{
	public:
		ComponentGUIFactory() = default;
		static AComponentGUI* CreateComponentGUI(Core::ComponentTypeId p_cTypeID, QWidget* p_parent = nullptr);
	};
}
