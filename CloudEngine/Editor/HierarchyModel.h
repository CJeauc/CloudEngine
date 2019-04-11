#pragma once

#include <QAbstractItemModel>
#include <QVariant>
#include "Core/Scene/SceneNode.h"

namespace QtEditor
{
	class HierarchyModel : public QAbstractItemModel
	{
		Q_OBJECT
	public:
		explicit HierarchyModel(QObject* p_parent = nullptr);
		~HierarchyModel();

		QVariant data(const QModelIndex& index, int role) const override;
		QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

		Qt::ItemFlags flags(const QModelIndex& index) const override;

		QModelIndex index(int row, int column, const QModelIndex& parent) const override;
		QModelIndex parent(const QModelIndex& child) const override;
		
		Qt::DropActions supportedDropActions() const override;
		Qt::DropActions supportedDragActions() const override;		

		QStringList mimeTypes() const override;
		QMimeData *mimeData(const QModelIndexList& indexes) const override;
		bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent) override;

		int rowCount(const QModelIndex& parent) const override;
		int columnCount(const QModelIndex& parent) const override;
		void Reset();

	private:
		Core::SceneNode* NodeForIndex(const QModelIndex &index) const;
		void RemoveNode(Core::SceneNode* p_node);

	protected:
		Core::SceneNode* m_root;
	};
}
