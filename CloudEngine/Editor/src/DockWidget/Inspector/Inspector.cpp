#include "stdafx.h"
#include "Inspector.h"

#include "Core/CoreEntity/GameObject.h"
#include "Core/Scene/SceneNode.h"
#include "Core/ECS/ECS.h"

#include <QMouseEvent>
#include <QLayout>
#include <QLabel>
#include <QTreeWidget>

#include "AComponentGUI.h"
#include "ComponentGUIFactory.h"
#include "Core/CoreComponent/Transform.h"

using namespace QtEditor;

Inspector::Inspector(QWidget* parent)
	:	QDockWidget("Inspector", parent), m_entitySelected(nullptr),
	m_treeWidget(nullptr), m_gameObjectName ( new EditableLabel(this))
{
	
	setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);	
	m_gameObjectName->setHidden(true);
	m_gameObjectName->GetLabel()->setAlignment(Qt::AlignCenter);
	
	connect(m_gameObjectName, SIGNAL(nameChanged(const QString&)), this, SLOT(OnNamedChanged(const QString&)));
}

Inspector::~Inspector()
{
	m_gameObjectName->deleteLater();
	for(auto& componentGUI: m_componentGUIs)
	{
		if(componentGUI.second)
		{
			delete componentGUI.second;
			componentGUI.second = nullptr;
		}
	}
	delete m_treeWidget;
}

void Inspector::EntitySelected(const QModelIndex& p_index)
{
	if(p_index.parent().isValid())
	{
		m_entitySelected = static_cast<Core::SceneNode*>(p_index.internalPointer())->GetGameObject();

 		m_gameObjectName->setVisible(true);
		m_gameObjectName->GetLabel()->setText(QString(m_entitySelected->Name().c_str()));

		AddComponentGUIFromGameObject(m_entitySelected);
		RemoveUnusedComponentGUIs(m_entitySelected);
	}
}

void Inspector::OnNamedChanged(const QString& p_name)
{
	m_entitySelected->SetName(p_name.toStdString());	
}

void Inspector::ResetInspector()
{	
	for (auto it = std::begin(m_componentGUIs); it != std::end(m_componentGUIs);)
	{
		it->second->RemoveFromTree(m_treeWidget);
		it->second->deleteLater();
		it = m_componentGUIs.erase(it);
	}
	m_entitySelected = nullptr;
	m_gameObjectName->GetLabel()->clear();
}

void Inspector::ReloadInspector()
{
	AddComponentGUIFromGameObject(m_entitySelected);
	RemoveUnusedComponentGUIs(m_entitySelected);
}


void Inspector::AddComponentGUI(std::shared_ptr<Core::AComponent> p_component)
{
	if(m_componentGUIs.find(p_component->GetComponentTypeId()) != m_componentGUIs.end())
	{
		m_componentGUIs[p_component->GetComponentTypeId()]->BindComponent(p_component);
	}
	else
	{			
		AComponentGUI* componentGUI = ComponentGUIFactory::CreateComponentGUI(p_component->GetComponentTypeId());
		if(!componentGUI)
		{
			SLOG(Log::Warning(), "Component type has no GUI");
		}
		m_componentGUIs[p_component->GetComponentTypeId()] = componentGUI;

		componentGUI->BindComponent(p_component);
		componentGUI->SetupFrame();
		componentGUI->AddToTree(m_treeWidget);			
	}
}

void Inspector::AddComponentGUIFromGameObject(Core::Entities::GameObject* p_gameObject)
{
	if(p_gameObject->GetComponent<Core::Components::Transform>())
	{
		AddComponentGUI(p_gameObject->GetComponent<Core::Components::Transform>());
	}

	for(auto component : p_gameObject->GetComponents())
	{
		if (component->GetComponentTypeId() == Core::Components::Transform::StaticComponentTypeId)
			continue;
		else
			AddComponentGUI(component);
	}

}

void Inspector::RemoveUnusedComponentGUIs(Core::Entities::GameObject* p_gameObject)
{
	std::vector<std::shared_ptr<Core::AComponent>> components = p_gameObject->GetComponents();

	for (auto it = std::begin(m_componentGUIs); it != std::end(m_componentGUIs);)
	{
		if (std::find_if(components.begin(), components.end(), [&it](std::shared_ptr<Core::AComponent> p_component) { return p_component->GetComponentTypeId() == it->first; }) == components.end())
		{
			it->second->RemoveFromTree(m_treeWidget);
			it->second->deleteLater();
			it = m_componentGUIs.erase(it);
		}
		else
			++it;
	}
}

void Inspector::Setup()
{
	this->setMinimumSize(300, 0);
	this->setWidget(m_treeWidget);

	m_treeWidget->setRootIsDecorated(false);
	m_treeWidget->setAlternatingRowColors(false);
	m_treeWidget->setIndentation(0);

	auto gameObjectNameItem = new QTreeWidgetItem;
	m_treeWidget->addTopLevelItem(gameObjectNameItem);
	m_treeWidget->setItemWidget(gameObjectNameItem, 0, m_gameObjectName);

	this->setAttribute(Qt::WA_WState_ExplicitShowHide);
}

void Inspector::AddWidgets(QTreeWidget *p_widget)
{
	m_treeWidget = p_widget;
}

EditableLabel* Inspector::GetEditableLabel()
{
	return m_gameObjectName;
}
