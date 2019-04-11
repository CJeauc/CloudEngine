#pragma once
#include <QWidget>
#include <QDockWidget>
#include "Core/ECS/Component/Component.h"
#include <qvalidator.h>
#include "EditableLabel.h"

class QTreeWidget;
class QLabel;

namespace QtEditor
{
	class AComponentGUI;

	class Inspector : public QDockWidget
	{
		Q_OBJECT
	public:
		explicit Inspector( QWidget *parent = nullptr);
		~Inspector();
		void Setup();
		void AddWidgets(QTreeWidget *p_widget);
		EditableLabel* GetEditableLabel();
		
	private slots:
		void EntitySelected(const QModelIndex& p_index);
		void OnNamedChanged(const QString& p_name);
		void ResetInspector();
		void ReloadInspector();

	private:
		void AddComponentGUI(std::shared_ptr<Core::AComponent> p_component);
		void AddComponentGUIFromGameObject(Core::Entities::GameObject* p_gameObject);
		void RemoveUnusedComponentGUIs(Core::Entities::GameObject* p_gameObject);
	
	private:
		Core::Entities::GameObject* m_entitySelected;
		QTreeWidget			*m_treeWidget;
		EditableLabel		*m_gameObjectName;
		std::unordered_map<Core::ComponentTypeId, AComponentGUI* > m_componentGUIs{};
	};
}
