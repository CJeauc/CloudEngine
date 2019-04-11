#include "stdafx.h"

#include "SceneWindow.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QGuiApplication>
#include "Core/CoreComponent/UniformRendering.h"
#include "Core/Scene/SceneManager.h"
#include <Core/CoreComponent/Transform.h>

#include <QApplication>
#include <QDesktopWidget>
#include <Core/Engine/CloudEngine.h>
#include <KeyMapper.h>

using namespace QtEditor;

Tools::Event<> SceneWindow::m_initializeEvent;

void SceneWindow::initializeGL()
{
	engine.Init();
	timer.start();

	m_initializeEvent.Invoke();

	/*Editor Setup*/
	Setup();

	this->setFocusPolicy(Qt::ClickFocus);
	this->setMouseTracking(true);
}

void SceneWindow::Setup()
{
	m_cameraSystem = Core::ECS::Get().AddSystem<Core::Systems::FPCameraSystem>();

	Core::ECS::Get().SetSystemCore<Core::Systems::FPCameraSystem>();

	m_camera = Core::ECS::Get().CreateEntity<Core::Entities::Daemon>("Editor Camera");
	m_camera->AddComponent<Core::Components::Transform>();
	m_cameraComp = m_camera->AddComponent<Core::Components::CameraComponent>(true);
	m_cameraComp->Sensitivity(0.02f);

	m_cameraSystem->AttachCamera(m_cameraComp);

	Core::ECS::Get().Awake();

	Core::Input::SetQt();
}


void SceneWindow::paintGL()
{
	makeCurrent();
	engine.Frame(timer.elapsed());
	update();

	Core::Input::SetMouseUpdate(true);
}

void SceneWindow::resizeGL(int p_width, int p_height)
{
	Rendering::Driver::SetViewport(p_width, p_height);
	Core::Components::UniformRendering::SetProjectionAspect(static_cast<float>(p_width) / static_cast<float>(p_height));
}


void SceneWindow::mousePressEvent(QMouseEvent* event)
{
	if (!m_isInFocus)
		return;

	QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));

	m_mouse = this->mapToGlobal(QPoint(event->x(), event->y()));
	m_isMousePressed = true;
	m_firstMouse = true;
}

void SceneWindow::mouseMoveEvent(QMouseEvent* event)
{
	if (m_isMousePressed)
	{
		if (event->buttons() & Qt::LeftButton)
		{
			QRect screenRect = QApplication::desktop()->screenGeometry();

			if (QCursor::pos().x() >= screenRect.width() - 1)
			{
				QCursor::setPos(2, QCursor::pos().y());
				Core::Input::SetMouseUpdate(false);
				m_firstMouse = true;
			}

			if (QCursor::pos().x() <= 1)
			{
				QCursor::setPos(screenRect.width() - 2, QCursor::pos().y());
				Core::Input::SetMouseUpdate(false);
				m_firstMouse = true;
			}

			if (QCursor::pos().y() >= screenRect.height() - 1)
			{
				QCursor::setPos(QCursor::pos().x(), 2);
				Core::Input::SetMouseUpdate(false);
				m_firstMouse = true;
			}

			if (QCursor::pos().y() <= 1)
			{
				QCursor::setPos(QCursor::pos().x(), screenRect.height() - 2);
				Core::Input::SetMouseUpdate(false);
				m_firstMouse = true;
			}

			if (m_firstMouse)
			{
				m_firstMouse = false;
				m_lastMouseX = QCursor::pos().x();
				m_lastMouseY = QCursor::pos().y();
				Core::Input::SetMouseUpdate(false);
				return;
			}

			float xOffset = m_lastMouseX - QCursor::pos().x();
			float yOffset = QCursor::pos().y() - m_lastMouseY;


			m_cameraComp->Yaw(m_cameraComp->Yaw() + yOffset * m_cameraComp->Sensitivity());
			m_cameraComp->Pitch(m_cameraComp->Pitch() + xOffset * m_cameraComp->Sensitivity());

			if (Core::Input::ShouldUpdateMouse())
			{ 
 				auto cameraTransform = m_camera->GetComponent<Core::Components::Transform>();
				cameraTransform->SetRotation(CloudMath::Vector3f( m_cameraComp->Yaw(),m_cameraComp->Pitch(), 0.0f));
			}

			m_lastMouseX = QCursor::pos().x();
			m_lastMouseY = QCursor::pos().y();
		}
	}
}

void SceneWindow::mouseReleaseEvent(QMouseEvent* event)
{
	QGuiApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
	m_isMousePressed = false;
	QCursor::setPos(m_mouse);
}



void SceneWindow::keyPressEvent(QKeyEvent* event)
{	
	if (!m_isInFocus)
		return;

	if (m_isMousePressed)
	{
		Core::Input::KeyCallBack(nullptr, KeyMapper::ToEngineInput(event->key()), 0, 1, 0);
		//SLOG(Log::Info(), "Pressed : " << event->key());
	}
}

void SceneWindow::keyReleaseEvent(QKeyEvent* event)
{
	if (!m_isInFocus)
		return;

	Core::Input::KeyCallBack(nullptr, KeyMapper::ToEngineInput(event->key()), 0, 0, 0);
	m_key = -1;
}

void SceneWindow::focusInEvent(QFocusEvent* event)
{
	if(event->reason() == Qt::MouseFocusReason)
		m_isInFocus = true;
}

void SceneWindow::focusOutEvent(QFocusEvent* event)
{
	m_isInFocus = false;
}

SceneWindow::SceneWindow(QWidget* parent)
{
	this->setParent(parent);
}
