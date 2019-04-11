#pragma once

#include <QFrame>
#include "Core/ECS/Component/AComponent.h"

class QTreeWidget;
class QTreeWidgetItem;
class QGridLayout;

namespace QtEditor
{
	class Category;

	class AComponentGUI : public QFrame
	{
		Q_OBJECT
	public :
		AComponentGUI(const std::string& p_name, QWidget* p_parent = nullptr);
		virtual void AddToTree(QTreeWidget* p_container);
		virtual void RemoveFromTree(QTreeWidget* p_container);

		virtual void BindComponent(std::shared_ptr<Core::AComponent> p_component) = 0;
		virtual void SetupFrame() = 0;

		inline const std::string& GetName() const { return m_name; }

		void AddField(const std::string&  p_labelName, QWidget* p_widget, int p_row);

	protected:
		std::string m_name;
		QTreeWidgetItem *m_titleContainer	{ nullptr };
		QTreeWidgetItem *m_contentContainer	{ nullptr };
		Category		*m_category			{ nullptr };
		QGridLayout		*m_mainGridLayout	{ nullptr };
		};
}