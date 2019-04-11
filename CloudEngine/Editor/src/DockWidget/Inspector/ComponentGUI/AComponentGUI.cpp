#include "stdafx.h"
#include "AComponentGUI.h"
#include "Category.h"

#include <QTreeWidgetItem>
#include <QGridLayout>
#include <QLabel>

using namespace QtEditor;

AComponentGUI::AComponentGUI(const std::string& p_name, QWidget* p_parent)
	: QFrame(p_parent), m_name(p_name), m_titleContainer(new QTreeWidgetItem()), m_contentContainer(new QTreeWidgetItem())
{
	m_contentContainer->setDisabled(true);
	m_titleContainer->addChild(m_contentContainer);

	m_mainGridLayout = new QGridLayout(p_parent);
	this->setLayout(m_mainGridLayout);
	this->setStyleSheet("background-color: rgb(50,50,50);");

}

void AComponentGUI::AddToTree(QTreeWidget* p_container)
{
	if(p_container)
	{
		p_container->addTopLevelItem(m_titleContainer);		
		
		 if(!m_category)
		{
			m_category = new Category(p_container, m_name.c_str(), m_titleContainer);
		}
		else
		{
			m_category->setParent(p_container);
		}
		
		p_container->setItemWidget(m_titleContainer, 0, m_category);
		p_container->setItemWidget(m_contentContainer, 0, this);
	}
}

void AComponentGUI::RemoveFromTree(QTreeWidget* p_container)
{
	m_titleContainer->removeChild(m_contentContainer);
	delete m_titleContainer;
}

void AComponentGUI::AddField(const std::string& p_labelName, QWidget* p_widget, int p_row)
{
	QLabel* fieldLabel = new QLabel(p_labelName.c_str());
	m_mainGridLayout->addWidget(fieldLabel, p_row, 0);
	m_mainGridLayout->addWidget(p_widget, p_row, 1);
}
