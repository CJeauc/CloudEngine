#include "HierarchyModel.h"

#include "Core/ECS/System/SystemManager.h"
#include "Core/Scene/SceneManager.h"
#include "SceneWindow.h"
#include "AssetsBrowser.h"
#include "Inspector.h"

#include <QMimeData>
#include <QCoreApplication>
#include <qstringlistmodel.h>

using namespace QtEditor;


HierarchyModel::HierarchyModel(QObject* p_parent)
	:QAbstractItemModel(p_parent), m_root(nullptr)
{
	SceneWindow::m_initializeEvent += BIND(&HierarchyModel::Reset, this);
	AssetsBrowser::m_switchingEvent += BIND(&HierarchyModel::Reset, this);
}

HierarchyModel::~HierarchyModel()
{
	delete m_root;
}

void HierarchyModel::Reset()
{
	beginResetModel();
	endResetModel();
	
	m_root = Core::SceneManagement::SceneManager::GetActiveScene()->GetRoot();
}

QVariant HierarchyModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if (role != Qt::DisplayRole)
		return QVariant();

	auto item = static_cast<Core::SceneNode*>(index.internalPointer());

	if (item->GetGameObject() == m_root->GetGameObject())
	{
		return Core::SceneManagement::SceneManager::GetActiveScene()->GetName().c_str();
	}
	return item->GetGameObject()->Name().c_str();
}

QVariant HierarchyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return m_root->GetGameObject()->Name().c_str();
	return 42; 
}

Qt::ItemFlags HierarchyModel::flags(const QModelIndex& index) const
{
	Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);
	if (!index.isValid())
		return Qt::ItemIsDropEnabled | defaultFlags;
	return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
}

QModelIndex HierarchyModel::index(int row, int column, const QModelIndex& parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	Core::SceneNode* parentNode = static_cast<Core::SceneNode*>(parent.internalPointer());;
	Core::SceneNode* childNode;

	if (!parent.isValid())
		childNode = m_root;
	else
		childNode = parentNode->GetChildAtIndex(row);

	if (childNode)
		return createIndex(row, column, childNode);
	else
		return QModelIndex();
}

QModelIndex HierarchyModel::parent(const QModelIndex& child) const
{
	if (!child.isValid())
		return QModelIndex();
	Core::SceneNode* indexNode = static_cast<Core::SceneNode*>(child.internalPointer());
	
	if (indexNode && indexNode->GetParent())
	{
		if (indexNode->GetParent()->GetGameObject() == m_root->GetGameObject() ||
			indexNode->GetParent()->GetParent()->GetGameObject() == nullptr)
		{
			return createIndex(0, 0, indexNode->GetParent());
		}
		std::vector<Core::SceneNode*>::iterator it = std::find(	indexNode->GetParent()->GetParent()->GetChildren().begin(),
																indexNode->GetParent()->GetParent()->GetChildren().end(), 
																indexNode->GetParent());

		return createIndex(std::distance(indexNode->GetParent()->GetParent()->GetChildren().begin(), it), 0, indexNode->GetParent());
	}
	else
		return QModelIndex();
}

Qt::DropActions HierarchyModel::supportedDropActions() const
{
	return Qt::MoveAction;
}

Qt::DropActions HierarchyModel::supportedDragActions() const
{
	return Qt::MoveAction;
}
static const char s_treeMimeType[] = "application/x-Core::SceneNode";

QStringList HierarchyModel::mimeTypes() const
{
	return QStringList() << s_treeMimeType;
}

QMimeData* HierarchyModel::mimeData(const QModelIndexList& indexes) const
{
	auto* mimeData = new QMimeData;
	QByteArray data;
	QDataStream stream(&data, QIODevice::WriteOnly);
	QList<Core::SceneNode*> nodes;

	foreach(const QModelIndex &index, indexes)
	{
		Core::SceneNode *node = NodeForIndex(index);
		if (!nodes.contains(node))
			nodes << node;
		
	}
	stream << QCoreApplication::applicationPid();
	stream << nodes.count();
	foreach(Core::SceneNode* node, nodes)
	{
		stream << reinterpret_cast<qlonglong>(node);
	}

	mimeData->setData(s_treeMimeType, data);
	return mimeData;
}

bool HierarchyModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
	const QModelIndex& parent)
{
	Q_ASSERT(action == Qt::MoveAction);
	Q_UNUSED(column);
	if (!data->hasFormat(s_treeMimeType))
		return false;

	QByteArray mimeData = data->data(s_treeMimeType);
	QDataStream stream(&mimeData, QIODevice::ReadOnly);
	qint64 senderPid;
	stream >> senderPid;
	if (senderPid != QCoreApplication::applicationPid())
		return false;

	Core::SceneNode* parentNode = NodeForIndex(parent);
	Q_ASSERT(parentNode);
	int count;
	stream >> count;

	if(row == -1)
	{
		if (!parent.isValid())
			row = 0;
		else
			row = rowCount(parent);			
	}

	for(int i = 0; i < count; ++i)
	{
		qlonglong nodePtr;
		stream >> nodePtr;
		auto *node = reinterpret_cast<Core::SceneNode*>(nodePtr);

		if (node->row() < row && parentNode == node->GetParent())
			--row;

		RemoveNode(node);

		beginInsertRows(parent, row, row);

		parentNode->AddChild(node);
		node->SetParent(parentNode);

		endInsertRows();

		++row;
	}
	return true;
}

int HierarchyModel::rowCount(const QModelIndex& parent) const
{
	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
		return 1;

	Core::SceneNode* parentNode = NodeForIndex(parent);
	return parentNode->GetChildren().size();
}

int HierarchyModel::columnCount(const QModelIndex& parent) const
{
	return 1;
}

Core::SceneNode* HierarchyModel::NodeForIndex(const QModelIndex& index) const
{
	if (!index.isValid())
		return m_root;
	else
		return static_cast<Core::SceneNode*>(index.internalPointer());
}

void HierarchyModel::RemoveNode(Core::SceneNode* p_node )
{
	const int row = p_node->row();
	QModelIndex index = createIndex(row, 0, p_node);

	beginRemoveRows(index.parent(), row, row);

	p_node->GetParent()->PopChild(p_node);
	endRemoveRows();
}
