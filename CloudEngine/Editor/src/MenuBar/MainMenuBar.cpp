#include "MainMenuBar.h"
#include "stdafx.h"
#include "Editor.h"
#include "Core/Scene/SceneManager.h"
#include "Core/CoreComponent/Transform.h"
#include "Core/CoreComponent/Physic/CapsuleCollider.h"
#include "GameObjectMenu.h"

using namespace QtEditor::Menu;

MainMenuBar::MainMenuBar(QWidget* parent)
	: QMenu(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	createActions();
}

void MainMenuBar::SetMenu(QMenuBar* p_menuBar)
{
	menuBar = p_menuBar;
	createMenus();
}

ComponentsMenu* MainMenuBar::GetComponentsMenu() const
{
	return componentsMenu;
}

GameObjectMenu* MainMenuBar::GetGameObjectMenu() const
{
	return gameObjectsMenu;
}


void MainMenuBar::newFile()
{
	SLOG(Log::Info(),  "Should create a file with this button .");
}

void MainMenuBar::openFile()
{
	SLOG(Log::Info(), "Should open a file or project with this button .");
}

void MainMenuBar::save()
{
	Core::SceneManagement::SceneManager::GetActiveScene()->Save();
}

void MainMenuBar::exit()
{
	QCoreApplication::quit();
}

void MainMenuBar::undo()
{
	SLOG(Log::Info(), "Should undo until a defined point with this button .");

}

void MainMenuBar::redo()
{
	SLOG(Log::Info(), "Should redo from defined point with this button .");

}

void MainMenuBar::idelete()
{
	SLOG(Log::Info(), "Should delete line or file with this button .");

}

void MainMenuBar::inspector()
{
	auto *inspector = this->parent()->findChild<Inspector*>();
	if (inspector->isHidden())
		inspector->setVisible(true);

}

void MainMenuBar::hierarchy()
{
	auto *hierarchy = this->parent()->findChild<Hierarchy*>();
	if (hierarchy->isHidden())
		hierarchy->setVisible(true);
}

void MainMenuBar::assetsBrowser()
{
	auto *assetsBrowser = this->parent()->findChild<AssetsBrowser*>();
	if (assetsBrowser->isHidden())
		assetsBrowser->setVisible(true); 	
}

void MainMenuBar::console()
{
	auto *console = this->parent()->findChild<Console*>();
	if (console->isHidden())
		console->setVisible(true);
}



void MainMenuBar::createActions()
{
	newAct = new QAction(tr("&New"), this);
	newAct->setShortcut(QKeySequence::New);
	newAct->setStatusTip(tr("Create a new file/project"));
	connect(newAct, &QAction::triggered, this, &MainMenuBar::newFile);

	openAct = new QAction(tr("&Open"), this);
	openAct->setStatusTip(tr("Open a file/project"));
	connect(openAct, &QAction::triggered, this, &MainMenuBar::openFile);
	
	saveAct = new QAction(tr("&Save"), this);
	saveAct->setShortcut(QKeySequence::Save);
	saveAct->setStatusTip(tr("save a file/project"));
	connect(saveAct, &QAction::triggered, this, &MainMenuBar::save);

	exitAct = new QAction(tr("&Exit"), this);
	exitAct->setStatusTip(tr("Close the window without saving the current project"));
	connect(exitAct, &QAction::triggered, this, &MainMenuBar::exit);

	undoAct = new QAction(tr("&Undo"));
	undoAct->setShortcut(QKeySequence::Undo);
	undoAct->setStatusTip("Undo");
	connect(undoAct, &QAction::triggered, this, &MainMenuBar::undo);

	redoAct = new QAction(tr("&Redo"));
	redoAct->setShortcut(QKeySequence::Redo);
	redoAct->setStatusTip("Redo");
	connect(redoAct, &QAction::triggered, this, &MainMenuBar::redo);

	ideleteAct = new QAction(tr("&Delete"));
	ideleteAct->setShortcut(QKeySequence::Delete);
	ideleteAct->setStatusTip("Delete");
	connect(ideleteAct, &QAction::triggered, this, &MainMenuBar::idelete);

	inspectorAct = new QAction(tr("&Inspector"));
	inspectorAct->setStatusTip("Open Inspector");
	connect(inspectorAct, &QAction::triggered, this, &MainMenuBar::inspector);

	hierarchyAct = new QAction(tr("&Hierarchy"));
	hierarchyAct->setStatusTip("Open Hierarchy");
	connect(hierarchyAct, &QAction::triggered, this, &MainMenuBar::hierarchy);

	assetsBrowserAct = new QAction(tr("&Asset Browser"));
	assetsBrowserAct->setStatusTip("Open the Asset Browser window");
	connect(assetsBrowserAct, &QAction::triggered, this, &MainMenuBar::assetsBrowser);

	consoleAct = new QAction(tr("&Console"));
	consoleAct->setStatusTip("Open the console window");
	connect(consoleAct, &QAction::triggered, this, &MainMenuBar::console);
}

void MainMenuBar::createMenus()
{
	fileMenu = this->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	editMenu = this->addMenu(tr("&Edit"));
	editMenu->addAction(undoAct);
	editMenu->addAction(redoAct);
	editMenu->addAction(ideleteAct);
	editMenu->addSeparator();

	viewMenu = this->addMenu(tr("&View"));
	viewMenu->addAction(inspectorAct);
	viewMenu->addAction(hierarchyAct);
	viewMenu->addAction(assetsBrowserAct);
	viewMenu->addAction(consoleAct);

	componentsMenu = new ComponentsMenu(this);
	gameObjectsMenu = new GameObjectMenu(this);

	componentsMenu->SetMenu(this->addMenu(tr("Component")));
	gameObjectsMenu->SetMenu(this->addMenu(tr("GameObject")));

	this->addMenu(tr("&GameObjects"));
	menuBar->addMenu(fileMenu);
	menuBar->addMenu(editMenu);
	menuBar->addMenu(viewMenu);
	menuBar->addMenu(gameObjectsMenu->GetGameObjectMenu());
	menuBar->addMenu(componentsMenu->GetComponentsMenu());
}
