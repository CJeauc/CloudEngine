#pragma once

#include <QWidget>
#include "core/CoreEntity/GameObject.h"

class QAction;
class QMenu;
namespace QtEditor
{
	namespace Menu
	{
		class GameObjectMenu : public QWidget
		{
			Q_OBJECT
		public :
			GameObjectMenu(QWidget* p_parent = nullptr);
			~GameObjectMenu();

			QMenu* GetGameObjectMenu();
			void SetMenu(QMenu* p_menu);

		signals:
			void reload();

		private slots:

			void createGameObject();
			void createCube();
			void createSphere();
			void createCapsule();
		private:
			void SetupActions();
			void SetupMenus();

		private:
			QMenu *gameObjects;
			QMenu *triDObjects;

			QAction *createGameObjectAct;
			QAction *createCubeAct;
			QAction *createSphereAct;
			QAction *createCapsuleAct;
		};
	}
}