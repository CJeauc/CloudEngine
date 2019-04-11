#pragma once
#include "AComponentGUI.h"

namespace QtEditor
{
	class MaterialComponentGUI : public AComponentGUI
	{
	public:
		explicit MaterialComponentGUI(const std::string& p_name, QWidget* p_parent = nullptr);
		~MaterialComponentGUI();

		void SetupFrame() override;
		void BindComponent(std::shared_ptr<Core::AComponent> p_component) override;
	};
}
