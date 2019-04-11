#pragma once
#include <QDockWidget>
#include <QtConcurrent/QtConcurrent>
#include <QFileInfoList>
#include "Core/Engine/CloudEngine.h"

class QTreeView;
class QListView;
class QFileSystemModel;
class QSplitter;
class QStandardItemModel;

namespace QtEditor
{

	class AssetsBrowser : public QDockWidget
	{
		Q_OBJECT

	public:
		explicit AssetsBrowser(QWidget *parent = nullptr);
		~AssetsBrowser();
		void Setup();
		void AddWidgets(QTreeView* p_directoryView, QListView* p_fileView, QSplitter *p_splitter);
	
	private:
		void ClickingOnScene(QFileInfo& p_fileInfo);

	signals:
		void UpdateItem(int, QPixmap);
		void SwitchingScene();
	
	public slots:
		void on_directoryView_clicked(const QModelIndex &index);
		void on_fileView_doubleClicked(const QModelIndex &index);
		void List(QFileInfoList filesList, QSize size);
		void setThumbs(int index, QPixmap img);

	private:
		QTreeView *directoryView;
		QListView *fileView;
		QSplitter *m_splitter;

		QString m_path;
		QStandardItemModel *m_fileItemModel;
		QFileSystemModel *m_directoryModel;

		QFuture<void> thread;
		bool m_isRunning;

	public:
		static Tools::Event<> m_switchingEvent;
	};
}