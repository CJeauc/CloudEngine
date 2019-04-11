#pragma once

#include<glad/glad.h>
#include "QOpenGLWidget"
#include "Core/Engine/CloudEngine.h"
#include <QElapsedTimer>
#include <Core/CoreEntity/Daemon.h>
#include <Core/CoreSystem/FPCameraSystem.h>
#include <Core/CoreComponent/CameraComponent.h>

namespace QtEditor
{
	class SceneWindow : public QOpenGLWidget
	{
		Core::CloudEngine engine;
		QElapsedTimer	  timer;

	public :
		explicit SceneWindow(QWidget *parent = nullptr);

	protected:
		void initializeGL() override;
		void paintGL() override ;
		void resizeGL(int p_width, int p_height) override;

		void mousePressEvent(QMouseEvent* event) override;
		void mouseMoveEvent(QMouseEvent* event) override;
		void mouseReleaseEvent(QMouseEvent* event) override;
		void keyPressEvent(QKeyEvent* event) override;
		void keyReleaseEvent(QKeyEvent* event) override;

		void focusInEvent(QFocusEvent* event) override;
		void focusOutEvent(QFocusEvent* event) override;

	private:
		void Setup();

	private:
		std::shared_ptr<Core::Entities::Daemon> m_camera;
		std::shared_ptr<Core::Components::CameraComponent> m_cameraComp;
		std::shared_ptr<Core::Systems::FPCameraSystem> m_cameraSystem;

		bool	m_isMousePressed{ false };
		bool	m_isInFocus{ false };

		QPoint	m_mouse {0,0};
		int		m_key{ -1 };
		bool m_firstMouse = true;

		float m_lastMouseX = 0;
		float m_lastMouseY = 0;

	public:
		static Tools::Event<> m_initializeEvent;

	};
}
