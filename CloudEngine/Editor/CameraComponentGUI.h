#pragma once
#include "AComponentGUI.h"

namespace QtEditor
{
	class CameraComponentGUI : public AComponentGUI
	{
	public:
		explicit CameraComponentGUI(const std::string& p_name, QWidget* p_parent = nullptr);
		~CameraComponentGUI();

		void SetupFrame() override;
		void BindComponent(std::shared_ptr<Core::AComponent> p_component) override;
	};
}
