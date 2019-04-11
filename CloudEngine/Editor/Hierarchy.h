#pragma once
#include <QDockWidget>
#include "HierarchyModel.h"

class QTreeView;

namespace QtEditor
{
	class Hierarchy : public QDockWidget
	{
		Q_OBJECT

	public:
		explicit Hierarchy(QWidget *parent = nullptr);
		void AddWidgets(QTreeView* p_treeView);
		void Setup();

		HierarchyModel* GetModel();
		QTreeView* GetView();
	public slots:
		void reloadHierarchy();

	private:
		QTreeView *m_hierarchy;
		HierarchyModel *m_hierarchyModel;
	};
}
