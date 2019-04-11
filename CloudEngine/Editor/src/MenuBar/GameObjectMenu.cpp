#include "stdafx.h"
#include "GameObjectMenu.h"

#include <QAction>
#include <QMenu>
#include "Core/Engine/CloudEngine.h"

using namespace QtEditor::Menu;

GameObjectMenu::GameObjectMenu(QWidget* p_parent)
	:QWidget(p_parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	SetupActions();

	gameObjects = new QMenu(this);
	triDObjects = new QMenu(gameObjects);
}

GameObjectMenu::~GameObjectMenu()
{
	gameObjects->deleteLater();
	triDObjects->deleteLater();
	createGameObjectAct->deleteLater();
	createCubeAct->deleteLater();
	createSphereAct->deleteLater();
	createCapsuleAct->deleteLater();
}

QMenu* GameObjectMenu::GetGameObjectMenu()
{
	return gameObjects;
}

void GameObjectMenu::SetMenu(QMenu* p_menu)
{
	gameObjects = p_menu;
	SetupMenus();
}

void GameObjectMenu::createGameObject()
{
	Core::ECS::Get().CreateEntity<Core::Entities::GameObject>("GameObject");
	emit reload();
}

void GameObjectMenu::createCube()
{
	Core::CloudEngine::CreateCubeEntity("Cube", CloudMath::Vector3f(0, 0, 0));
	emit reload();
}

void GameObjectMenu::createSphere()
{
	Core::CloudEngine::CreateSphereEntity("Sphere", CloudMath::Vector3f(0, 0, 0));
	emit reload();
}

void GameObjectMenu::createCapsule()
{
}

void GameObjectMenu::SetupActions()
{
	createGameObjectAct = new QAction(tr("GameObject"));
	createGameObjectAct->setStatusTip("Create an empty game Object.");
	connect(createGameObjectAct, &QAction::triggered, this, &GameObjectMenu::createGameObject);

	createCubeAct = new QAction(tr("Cube"));
	createCubeAct->setStatusTip("Create a cube at position 0,0,0 .");
	connect(createCubeAct, &QAction::triggered, this, &GameObjectMenu::createCube);

	createSphereAct = new QAction(tr("Sphere"));
	createSphereAct->setStatusTip("Create a sphere at position 0,0,0 .");
	connect(createSphereAct, &QAction::triggered, this, &GameObjectMenu::createSphere);

	createCapsuleAct = new QAction(tr("Capsule"));
	createCapsuleAct->setStatusTip("Create a capsule at position 0,0,0 .");
	connect(createCapsuleAct, &QAction::triggered, this, &GameObjectMenu::createCapsule);
}

void GameObjectMenu::SetupMenus()
{
	gameObjects->addAction(createGameObjectAct);

	triDObjects = gameObjects->addMenu(tr("&3D Objects"));
	triDObjects->addAction(createCubeAct);
	triDObjects->addAction(createSphereAct);
	triDObjects->addAction(createCapsuleAct);
}
