#include "stdafx.h"
#include "Category.h"

using namespace QtEditor;

Category::Category(QTreeWidget* p_parent, const QString& p_text, QTreeWidgetItem* p_item)
	: QPushButton(p_text, p_parent), m_item(p_item)
{
	connect(this, SIGNAL(pressed()), this, SLOT(ButtonPressed()));
	m_item->setExpanded(true);
	this->setStyleSheet("background-color: rgb(30,30,30);");
}

void Category::ButtonPressed()
{
	m_item->setExpanded(!m_item->isExpanded());
}
