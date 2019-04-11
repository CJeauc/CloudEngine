#include "stdafx.h"
#include "AssetsBrowser.h"
#include "Core/Scene/SceneManager.h"
#include "NotificationsBox.h"

#include <QTreeView>
#include <QListView>
#include <QApplication>
#include <QSplitter>
#include <QAbstractItemView>
#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QHeaderView>

using namespace QtEditor;
Tools::Event<> AssetsBrowser::m_switchingEvent;

AssetsBrowser::AssetsBrowser(QWidget* parent)
	:QDockWidget("AssetsBrowser", parent), directoryView(nullptr), fileView(nullptr), m_splitter(nullptr), m_fileItemModel (nullptr), m_directoryModel(nullptr), m_isRunning(false)
{
	setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
	this->setFocusPolicy(Qt::ClickFocus);

	QThreadPool::globalInstance()->setMaxThreadCount(1);
}

AssetsBrowser::~AssetsBrowser()
{
	delete directoryView;
	delete fileView;
	delete m_fileItemModel;
	delete m_splitter;
	delete m_directoryModel;
}

void AssetsBrowser::Setup()
{
	this->setMinimumSize(200, 0);
	this->setWidget(m_splitter);

	directoryView->setMinimumWidth(250);
	directoryView->setMaximumWidth(300);
	
	m_path = QApplication::applicationDirPath() + "/../../../Resources";

	m_directoryModel = new QFileSystemModel(this);
	m_directoryModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
	directoryView->setModel(m_directoryModel);
	m_directoryModel->setRootPath(m_path);

	QModelIndex index = m_directoryModel->index(m_path);
	if (index.isValid())
	{
		directoryView->setRootIndex(index);
		directoryView->hideColumn(1);
		directoryView->hideColumn(2);
		directoryView->hideColumn(3);
		directoryView->setHeaderHidden(true);
	}
	
	m_fileItemModel = new QStandardItemModel(this);

	fileView->setIconSize(QSize(80, 80));
	fileView->setViewMode(QListView::IconMode);
	fileView->setModel(m_fileItemModel);	
	
	QObject::connect(directoryView,SIGNAL(clicked(const QModelIndex&)), this, SLOT(on_directoryView_clicked(const QModelIndex&)));
	connect(this, SIGNAL(UpdateItem(int, QPixmap)), SLOT(setThumbs(int, QPixmap)));
	QObject::connect(fileView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(on_fileView_doubleClicked(const QModelIndex&)));

	directoryView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	m_isRunning = false;
}

void AssetsBrowser::AddWidgets(QTreeView* p_directoryView, QListView* p_fileView, QSplitter *p_splitter)
{
	directoryView = p_directoryView;
	fileView		= p_fileView;
	m_splitter		= p_splitter;
}

void AssetsBrowser::ClickingOnScene(QFileInfo& p_fileInfo)
{
	QString fileBaseName(p_fileInfo.baseName());
	QString ActiveSceneName(Core::SceneManagement::SceneManager::GetActiveScene()->GetName().c_str());

	NotificationsBox *saveBox = new NotificationsBox(this);
	
	switch(saveBox->SaveNotifications(ActiveSceneName))
	{
	case 1:
		Core::SceneManagement::SceneManager::GetActiveScene()->Save();
		Core::SceneManagement::SceneManager::LoadScene(p_fileInfo.baseName().toStdString());
		m_switchingEvent.Invoke();
		break;
	case 0:
		Core::SceneManagement::SceneManager::LoadScene(p_fileInfo.baseName().toStdString());
		m_switchingEvent.Invoke();
		break;
	case -1:
		break;
	}
}

void AssetsBrowser::on_directoryView_clicked(const QModelIndex& index)
{
	m_fileItemModel->clear();
	
	m_isRunning = false;
	thread.waitForFinished();
	QDir dir(m_directoryModel->filePath(directoryView->currentIndex()));
	QFileInfoList filesList;

	if (dir.path().contains("Model"))
		filesList = dir.entryInfoList(QStringList() << "*.obj" << "*.fbx", QDir::Files);
	else
		filesList = dir.entryInfoList(QStringList() << "*.jpg" << "*.png" << "*.fs" << "*.vs" << "*.ico" << "*.cloud" , QDir::Files);
	
	int filesCount = filesList.size();

	QPixmap placeholder = QPixmap(fileView->iconSize());
	placeholder.fill(Qt::gray);

	for(int i =0; i < filesCount; i++)
	{
		m_fileItemModel->setItem(i, new QStandardItem(QIcon(placeholder), filesList[i].fileName()));
		m_fileItemModel->item(i,0)->setEditable(false);
	}

	m_isRunning = true;
	thread = QtConcurrent::run(this, &AssetsBrowser::List, filesList, fileView->iconSize());
}

void AssetsBrowser::List(QFileInfoList filesList, QSize size)
{
	int filesCount = filesList.size();
	for(int i = 0; m_isRunning && i<filesCount; i++)
	{
		QPixmap originalImage(filesList[i].filePath());

		if (filesList[i].suffix().contains(tr("fs")) || filesList[i].suffix().contains(tr("vs")))
		{
			QPixmap shaderIcon("Resources/SIcon.png");

			if (!m_isRunning)
				return;
			emit UpdateItem(i, shaderIcon);
		}

		if(!originalImage.isNull())
		{
			QPixmap scaledImage = originalImage.scaled(size);
			if (!m_isRunning)
				return;
			emit UpdateItem(i, scaledImage);
		}
	}
}

void AssetsBrowser::setThumbs(int index, QPixmap img)
{
	QIcon icon = QIcon(img);
	QStandardItem *item = m_fileItemModel->item(index);
	m_fileItemModel->setItem(index, new QStandardItem(icon, item->text()));
}

void AssetsBrowser::on_fileView_doubleClicked(const QModelIndex& index)
{
	QFileInfo fileInfo(index.data().toString());

	if (fileInfo.suffix().contains(tr("cloud") , Qt::CaseSensitive))
	{
		ClickingOnScene(fileInfo);
		emit SwitchingScene();
	}
}


