#include "stdafx.h"
#include "ComponentsMenu.h"
#include "Core/Scene/SceneNode.h"
#include "Core/CoreComponent/Transform.h"
#include "Core/CoreComponent/MeshRenderer.h"
#include "Core/CoreComponent/MaterialRenderer.h"

#include <QAction>
#include <QModelIndex>
#include <QMenu>
#include "Core/Managers/ResourceManager.h"

using namespace QtEditor::Menu;

ComponentsMenu::ComponentsMenu(QWidget* p_parent)
	: QWidget(p_parent), m_gameObject(nullptr)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	SetupAction();

	componentsMenu = new QMenu(this);
	physicalObjects = new QMenu(componentsMenu);
}

ComponentsMenu::~ComponentsMenu()
{
	transformAct->deleteLater();
	meshRendererAct->deleteLater();
	materialRendererAct->deleteLater();
	boxColliderAct->deleteLater();
	sphereColliderAct->deleteLater();
	capsuleColliderAct->deleteLater();
	rigidbodyAct->deleteLater();
	cameraComponentAct->deleteLater();
	firstPersonControllerAct->deleteLater();
}

QMenu* ComponentsMenu::GetComponentsMenu()  
{
	return componentsMenu;
}

void ComponentsMenu::SetMenu(QMenu* p_menu)
{
	componentsMenu = p_menu;

	SetupMenus();
}

void ComponentsMenu::createAndAttachTransform()
{
	if (m_gameObject)
	{
		if (!m_gameObject->GetComponent<Core::Components::Transform>())
		{
			m_gameObject->AddComponent<Core::Components::Transform>();
			emit reload();
		}
	}
}

void ComponentsMenu::createAndAttachMeshRenderer()
{
	if (m_gameObject)
	{
		if (!m_gameObject->GetComponent<Core::Components::MeshRenderer>())
		{
			m_gameObject->AddComponent<Core::Components::MeshRenderer>();
			auto material = std::make_shared<Rendering::Material>(Cloud::Get().ResourceManager<Rendering::Shader>()->GetResource("Default").get());
			material->SetTextureToSlot(material->GetTextureSlotByName("diffuseTex"),
				Cloud::Get().ResourceManager<Rendering::Texture>()->GetResource("BoxDiffuse").get());
			material->SetTextureToSlot(material->GetTextureSlotByName("specularTex"),
				Cloud::Get().ResourceManager<Rendering::Texture>()->GetResource("BoxSpecular").get());
			auto materialRendererComponent = m_gameObject->AddComponent<Core::Components::MaterialRenderer>(material);
			emit reload();
		}
	}
}

void ComponentsMenu::createAndAttachMaterialRenderer()
{
}

void ComponentsMenu::createAndAttachBoxCollider()
{
}

void ComponentsMenu::createAndAttachSphereCollider()
{
}

void ComponentsMenu::createAndAttachCapsuleCollider()
{
}

void ComponentsMenu::createAndAttachRigidBody()
{
}

void ComponentsMenu::createAndAttachCameraComponent()
{
}

void ComponentsMenu::createAndAttachFirstPersonController()
{
}

void ComponentsMenu::EntitySelected(const QModelIndex& p_index)
{
	m_gameObject = static_cast<Core::SceneNode*>(p_index.internalPointer())->GetGameObject();

	if(m_gameObject)
		SLOG(Log::Info(), m_gameObject->Name());
}

void ComponentsMenu::SetupAction()
{
	transformAct = new QAction(tr("&Transform"), this);
	transformAct->setStatusTip(tr("Attach a new transform"));
	connect(transformAct, &QAction::triggered, this, &ComponentsMenu::createAndAttachTransform);

	meshRendererAct = new QAction(tr("&Mesh Renderer"), this);
	meshRendererAct->setStatusTip(tr("Attach a new mesh renderer"));
	connect(meshRendererAct, &QAction::triggered, this, &ComponentsMenu::createAndAttachMeshRenderer);
	
	materialRendererAct = new QAction(tr("&Material Renderer"), this);
	materialRendererAct->setStatusTip(tr("Attach a new material renderer"));
	connect(materialRendererAct, &QAction::triggered, this, &ComponentsMenu::createAndAttachMaterialRenderer);

	boxColliderAct = new QAction(tr("&Box Collider"), this);
	boxColliderAct->setStatusTip(tr("Attach a new Box Collider"));
	connect(boxColliderAct, &QAction::triggered, this, &ComponentsMenu::createAndAttachBoxCollider);

	sphereColliderAct = new QAction(tr("&Sphere Collider"), this);
	sphereColliderAct->setStatusTip(tr("Attach a new sphere Collider"));
	connect(sphereColliderAct, &QAction::triggered, this, &ComponentsMenu::createAndAttachSphereCollider);

	capsuleColliderAct = new QAction(tr("&Capsule Collider"), this);
	capsuleColliderAct->setStatusTip(tr("Attach a new Capsule Collider"));
	connect(capsuleColliderAct, &QAction::triggered, this, &ComponentsMenu::createAndAttachCapsuleCollider);

	rigidbodyAct = new QAction(tr("&RigidBody"), this);
	rigidbodyAct->setStatusTip(tr("Attach a new rigidBody"));
	connect(rigidbodyAct, &QAction::triggered, this, &ComponentsMenu::createAndAttachRigidBody);
	
	cameraComponentAct = new QAction(tr("&Camera"), this);
	cameraComponentAct->setStatusTip(tr("Attach a new camera"));
	connect(cameraComponentAct, &QAction::triggered, this, &ComponentsMenu::createAndAttachCameraComponent);

	firstPersonControllerAct = new QAction(tr("&First Person Controller"), this);
	firstPersonControllerAct->setStatusTip(tr("Attach a new First Person Controller component"));
	connect(firstPersonControllerAct, &QAction::triggered, this, &ComponentsMenu::createAndAttachFirstPersonController);
}

void ComponentsMenu::SetupMenus()
{
	componentsMenu->addAction(transformAct);
	componentsMenu->addAction(meshRendererAct);
	componentsMenu->addAction(materialRendererAct);

	physicalObjects = componentsMenu->addMenu(tr("Collider"));

	physicalObjects->addAction(boxColliderAct);
	physicalObjects->addAction(sphereColliderAct);
	physicalObjects->addAction(capsuleColliderAct);
	physicalObjects->addAction(rigidbodyAct);

	componentsMenu->addAction(cameraComponentAct);
	componentsMenu->addAction(firstPersonControllerAct);
}
