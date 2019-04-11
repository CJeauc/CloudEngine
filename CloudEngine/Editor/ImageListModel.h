#pragma once
#include <QAbstractListModel>
#include <QPixmap>

struct PixmapPair
{
	QString _file;
	QPixmap _small;
	QPixmap _large;
};

namespace QtEditor
{
	class ImageListModel : public QAbstractListModel
	{
		Q_OBJECT
	public:
		enum Roles
		{
			LargePixmapRole = Qt::UserRole + 1
		};
		explicit ImageListModel(std::initializer_list<QString> files, QObject *parent = 0);
		virtual ~ImageListModel();

	public:
		int rowCount(const QModelIndex &parent) const;
		QVariant data(const QModelIndex &index, int role) const;

	private:
		QList<PixmapPair*> _data;
	};
}