#include "ImageListModel.h"

using namespace QtEditor;

ImageListModel::ImageListModel(std::initializer_list<QString> files, QObject* parent)
	: QAbstractListModel(parent)
{
	auto iter = files.begin();
	while (iter != files.end())
	{
		QPixmap large(*iter);
		PixmapPair *pair = new PixmapPair();
		pair->_file = *iter;
		pair->_large = large;
		pair->_small = large.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		_data.append(pair);
		++iter;
	}
}

ImageListModel::~ImageListModel()
{
	qDeleteAll(_data);
}

int ImageListModel::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid())
		return 0;
	else
		return _data.count();
}

QVariant ImageListModel::data(const QModelIndex& index, int role) const
{
	if(index.isValid())
	{
		switch(role)
		{
		case Qt::DecorationRole:
			return _data.value(index.row())->_small;
		case Qt::DisplayRole:
			return _data.value(index.row())->_file;
		case LargePixmapRole:
			return _data.value(index.row())->_large;
		}
	}
	return QVariant();
}


