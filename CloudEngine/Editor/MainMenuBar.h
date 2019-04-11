#pragma once
#include <QMenuBar>

#include "ComponentsMenu.h"
#include "GameObjectMenu.h"

namespace QtEditor
{
	namespace Menu
	{
		class MainMenuBar : public QMenu
		{
			Q_OBJECT

		public:
			MainMenuBar(QWidget *parent = nullptr);
			void SetMenu(QMenuBar *p_menuBar);

			ComponentsMenu* GetComponentsMenu() const;
			GameObjectMenu* GetGameObjectMenu() const;

		private slots:
			void newFile();
			void openFile();
			void save();
			void exit();

			void undo();
			void redo();
			void idelete();

			void inspector();
			void hierarchy();
			void assetsBrowser();
			void console();

		private:
			void createActions();
			void createMenus();

			QMenuBar *menuBar;

			QMenu *fileMenu;
			QMenu *editMenu;
			QMenu *viewMenu;

			ComponentsMenu *componentsMenu;
			GameObjectMenu *gameObjectsMenu;

			QAction *newAct;
			QAction *openAct;
			QAction *saveAct;
			QAction *exitAct;

			QAction *undoAct;
			QAction *redoAct;
			QAction *ideleteAct;

			QAction *inspectorAct;
			QAction *hierarchyAct;
			QAction *assetsBrowserAct;
			QAction *consoleAct;
		};
	}
}
