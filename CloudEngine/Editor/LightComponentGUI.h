#pragma once
#include "AComponentGUI.h"

namespace QtEditor
{
	class LightComponentGUI : public AComponentGUI
	{
	public:
		explicit LightComponentGUI(const std::string& p_name, QWidget* p_parent = nullptr);
		~LightComponentGUI();

		void SetupFrame() override;
		void BindComponent(std::shared_ptr<Core::AComponent> p_component) override;
	};
}
