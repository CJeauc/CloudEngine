#pragma once
#include "ui_Editor.h"
#include "SceneWindow.h"

#include <QtWidgets/QMainWindow>
#include "Inspector.h"
#include "Console.h"
#include "Hierarchy.h"
#include "AssetsBrowser.h"
#include "MainMenuBar.h"

namespace Ui
{
	class EditorClass;
}

class QAction;
class QMenu;

class Editor : public QMainWindow
{
	Q_OBJECT

public:
	explicit Editor(QWidget *parent = 0);
	~Editor();

	void CreateInspector();
	void CreateScene();
	void CreateConsole();
	void CreateHierarchy();
	void CreateAssetsBrowser();
	void CreateMenu();

	void AddDockWidgets();

private:
	QtEditor::SceneWindow *window;
	QtEditor::Inspector *inspector;
	QtEditor::Console *console;
	QtEditor::Hierarchy *hierarchy;
	QtEditor::AssetsBrowser *assetsBrowser;
	QtEditor::Menu::MainMenuBar *menuBar;

	Ui::EditorClass m_ui;
};
