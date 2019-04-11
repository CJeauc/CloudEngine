#include "stdafx.h"
#include "TransformComponentGUI.h"

#include "Core/CoreComponent/Transform.h"
#include <QHBoxLayout>
#include <QLabel>
#include <Vec3Widget.h>

using namespace QtEditor;

TransformComponentGUI::TransformComponentGUI(const std::string& p_name, QWidget* p_parent)
	: AComponentGUI(p_name, p_parent), m_transform(nullptr), m_positions{new Vec3Widget(CloudMath::Vector3f(0, 0, 0))}, m_rotations{new Vec3Widget(CloudMath::Vector3f(0,0,0)) }, m_scalers {new Vec3Widget(CloudMath::Vector3f(0, 0, 0))}
{
	Setup();
}

TransformComponentGUI::~TransformComponentGUI()
{
}

void QtEditor::TransformComponentGUI::Setup()
{
	connect(m_positions, SIGNAL(ValueChangedFromVec3(CloudMath::Vector3f)), this, SLOT(OnValuePositionChanged(CloudMath::Vector3f)));
	connect(m_rotations, SIGNAL(ValueChangedFromVec3(CloudMath::Vector3f)), this, SLOT(OnValueRotationChanged(CloudMath::Vector3f)));
	connect(m_scalers, SIGNAL(ValueChangedFromVec3(CloudMath::Vector3f)), this, SLOT(OnValueScaleChanged(CloudMath::Vector3f)));
}


void TransformComponentGUI::SetupFrame()
{
	if (m_transform)
	{
		SmartLabel* positions = new SmartLabel(QString("Position "));
		positions->setFixedWidth(55);
		m_mainGridLayout->addWidget(positions, 0, 0, Qt::AlignCenter);
		m_mainGridLayout->addWidget(m_positions, 0, 1, Qt::AlignCenter);
		m_mainGridLayout->setRowMinimumHeight(0, 30);

		
		SmartLabel* rotation = new SmartLabel(QString("Rotation"));
		rotation->setFixedWidth(55);
		m_mainGridLayout->addWidget(rotation, 1, 0, Qt::AlignCenter);
		m_mainGridLayout->addWidget(m_rotations, 1, 1, Qt::AlignCenter);
		m_mainGridLayout->setRowMinimumHeight(1, 30);

		SmartLabel* scale = new SmartLabel(QString("Scale"));
		scale->setFixedWidth(55);
		m_mainGridLayout->addWidget(scale, 2, 0, Qt::AlignCenter);
		m_mainGridLayout->addWidget(m_scalers, 2, 1, Qt::AlignCenter);
		m_mainGridLayout->setRowMinimumHeight(2, 30);

		m_mainGridLayout->setSpacing(0);
		m_mainGridLayout->setVerticalSpacing(0);

		m_mainGridLayout->setMargin(0);
		m_mainGridLayout->setContentsMargins(0,0,0,0);
		
	}
}

void TransformComponentGUI::BindComponent(std::shared_ptr<Core::AComponent> p_component)
{
	m_transform = std::static_pointer_cast<Core::Components::Transform>(p_component);

	SetupPositions();
	SetupRotations();
	SetupScale();
}

void TransformComponentGUI::SetupPositions() const
{ 
	m_positions->SetVec3(m_transform->GetPosition());
}

void TransformComponentGUI::SetupRotations() const
{ 
	m_rotations->SetVec3(m_transform->GetRotation().ToEuler());
}

void TransformComponentGUI::SetupScale() const
{
	m_scalers->SetVec3(m_transform->GetScale());
}

void QtEditor::TransformComponentGUI::OnValueScaleChanged(CloudMath::Vector3f p_vector) const
{
	m_transform->SetScale(p_vector);
}

void QtEditor::TransformComponentGUI::OnValueRotationChanged(CloudMath::Vector3f p_vector) const
{
	m_transform->SetRotation(p_vector);
}

void TransformComponentGUI::OnValuePositionChanged(CloudMath::Vector3f p_vector) const
{
	m_transform->SetPosition(p_vector);
}


