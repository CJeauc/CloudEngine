#include "Editor.h"
#include <QShortcut>
#include <QSplitter>
#include "MainMenuBar.h"
#include <QDesktopWidget>

Editor::Editor(QWidget *parent)
	:	QMainWindow(parent)
{
	m_ui.setupUi(this);
	setDockOptions(DockOption::AllowNestedDocks | DockOption::AnimatedDocks | DockOption::AllowTabbedDocks);

	CreateConsole();
	CreateAssetsBrowser();
	CreateScene();
	
	CreateInspector();
	CreateHierarchy();
	CreateMenu();

	connect(assetsBrowser, SIGNAL(SwitchingScene()), inspector, SLOT(ResetInspector()));
	connect(this->inspector->GetEditableLabel(), SIGNAL(nameChanged()), this->hierarchy, SLOT(reloadHierarchy()));
	connect(hierarchy->GetView(), SIGNAL(clicked(const QModelIndex&)), inspector, SLOT(EntitySelected(const QModelIndex&)));

	connect(this->hierarchy->GetView(), SIGNAL(clicked(const QModelIndex&)), menuBar->GetComponentsMenu(), SLOT(EntitySelected(const QModelIndex&)));
	connect(this->menuBar->GetComponentsMenu(), SIGNAL(reload()), this->inspector, SLOT(ReloadInspector()));
	connect(this->menuBar->GetGameObjectMenu(), SIGNAL(reload()), this->hierarchy, SLOT(reloadHierarchy()));

	this->AddDockWidgets();
	this->showMaximized();
}

Editor::~Editor()
{
	delete window;
	delete inspector;
	delete console;
	delete hierarchy;
	delete assetsBrowser;
	delete menuBar;
}

void Editor::CreateInspector()
{
	inspector = new QtEditor::Inspector(this);
	inspector->AddWidgets(m_ui.Inspector);
	inspector->Setup();
}

void Editor::CreateScene()
{
	window = new QtEditor::SceneWindow(this);
	m_ui.splitter->setStretchFactor(0, 0);
	m_ui.splitter->setStretchFactor(1, 5);
	m_ui.splitter->setStretchFactor(2, 0);

	m_ui.MainFrameSplitter->addWidget(window);
}

void Editor::CreateConsole()
{
	console = new QtEditor::Console(this);
}

void Editor::CreateHierarchy()
{
	hierarchy = new QtEditor::Hierarchy(this);
	hierarchy->AddWidgets(m_ui.Hierarchy);
	hierarchy->Setup();

}

void Editor::CreateAssetsBrowser()
{
	assetsBrowser = new QtEditor::AssetsBrowser(this);
	assetsBrowser->AddWidgets(m_ui.DirectoriesTree, m_ui.listView, m_ui.AssetBrowserSplit);
	assetsBrowser->Setup();
}

void Editor::CreateMenu()
{
	menuBar = new QtEditor::Menu::MainMenuBar(this);
	menuBar->SetMenu(m_ui.menuBar);
}

void Editor::AddDockWidgets()
{
	addDockWidget(Qt::BottomDockWidgetArea, assetsBrowser);
	addDockWidget(Qt::BottomDockWidgetArea, console);
	addDockWidget(Qt::LeftDockWidgetArea, hierarchy);
	addDockWidget(Qt::RightDockWidgetArea, inspector);
}
