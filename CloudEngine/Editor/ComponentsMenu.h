#pragma once
#include <QWidget>
#include "Core/CoreEntity/GameObject.h"

class QAction;
class QModelIndex;
class QMenu;

namespace QtEditor
{
	namespace Menu
	{
		class ComponentsMenu : public QWidget
		{
			Q_OBJECT

		public:
			ComponentsMenu(QWidget* p_parent = nullptr);
			~ComponentsMenu();

			QMenu* GetComponentsMenu();
			void SetMenu(QMenu* p_menu);

		signals:
			void reload();

		public slots:
			void EntitySelected(const QModelIndex& p_index);

		private slots:
			void createAndAttachTransform();
			void createAndAttachMeshRenderer();
			void createAndAttachMaterialRenderer();
			void createAndAttachBoxCollider();
			void createAndAttachSphereCollider();
			void createAndAttachCapsuleCollider();
			void createAndAttachRigidBody();
			void createAndAttachCameraComponent();
			void createAndAttachFirstPersonController();

		private:
			void SetupAction();
			void SetupMenus();

		private:
			QAction *transformAct;
			QAction *meshRendererAct;
			QAction *materialRendererAct;
			QAction *boxColliderAct;
			QAction *sphereColliderAct;
			QAction *capsuleColliderAct;
			QAction *rigidbodyAct;
			QAction *cameraComponentAct;
			QAction *firstPersonControllerAct;

			QMenu	*componentsMenu;
			QMenu	*physicalObjects;

			Core::Entities::GameObject* m_gameObject;
		};

	}
}