#include "stdafx.h"
#include "Hierarchy.h"
#include <QTreeView>
#include <QHeaderView>

using namespace QtEditor;

Hierarchy::Hierarchy(QWidget* parent)
	:QDockWidget("Hierarchy", parent), m_hierarchy(nullptr)
{
	this->setFocusPolicy(Qt::ClickFocus);
}

void Hierarchy::AddWidgets(QTreeView* p_treeView)
{
	m_hierarchy = p_treeView;
}

void Hierarchy::Setup()
{
	this->setMinimumSize(300, 780);
	this->setWidget(m_hierarchy);
	this->setAttribute(Qt::WA_WState_ExplicitShowHide);

	m_hierarchyModel = new HierarchyModel();
	m_hierarchy->setModel(m_hierarchyModel);
	m_hierarchy->setSelectionMode(QAbstractItemView::SingleSelection);
	m_hierarchy->setDragDropMode(QAbstractItemView::InternalMove);
	m_hierarchy->setDragEnabled(true);
	m_hierarchy->setAcceptDrops(true);
	m_hierarchy->viewport()->setAcceptDrops(true);
	connect(this->m_hierarchy, &QTreeView::pressed, this->m_hierarchy, &QTreeView::expandAll);
	this->m_hierarchy->header()->setVisible(false);
	this->m_hierarchy->setEditTriggers(QAbstractItemView::EditTriggers());
}

HierarchyModel* Hierarchy::GetModel()
{
	return m_hierarchyModel;
}

QTreeView* Hierarchy::GetView()
{
	return m_hierarchy;
}

void Hierarchy::reloadHierarchy()
{
	m_hierarchyModel->Reset();
	m_hierarchy->expandAll();
}
