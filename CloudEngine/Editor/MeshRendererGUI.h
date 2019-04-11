#pragma once
#include "AComponentGUI.h"
#include "Core/CoreComponent/MeshRenderer.h"

class QComboBox;

namespace QtEditor
{
	class MeshRendererGUI: public AComponentGUI
	{
		Q_OBJECT

	public:
		explicit MeshRendererGUI(const std::string& p_name, QWidget* p_parent = nullptr);
		~MeshRendererGUI();

		void SetupFrame() override;
		void BindComponent(std::shared_ptr<Core::AComponent> p_component) override;
	signals:
		void currentIndexChanged(int index);

	private slots:
		void SetModel(QString p_fileName);

	private:
		std::shared_ptr<Core::Components::MeshRenderer>  m_meshComponent;
		QComboBox										*m_meshBox;

	};
}
