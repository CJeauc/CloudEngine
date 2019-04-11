#include "stdafx.h"
#include "Vec3Widget.h"

#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include "Inspector.h"
#include <SmartLabel.h>
#include <SmartLabelEdit.h>

using namespace QtEditor;

Vec3Widget::Vec3Widget(const CloudMath::Vector3f& p_vector,
	QWidget* p_parent)
	: QWidget(p_parent),m_vector(p_vector), m_layout(nullptr)
{
	m_xBox = new SmartLabelEdit(QString("x : "), this);
	m_yBox = new SmartLabelEdit(QString("y : "), this);
	m_zBox = new SmartLabelEdit(QString("z : "), this);

	connect(m_xBox, SIGNAL(ValueChanged(double)), this, SLOT(OnValueChangedX(double)));
	connect(m_yBox, SIGNAL(ValueChanged(double)), this, SLOT(OnValueChangedY(double)));
	connect(m_zBox, SIGNAL(ValueChanged(double)), this, SLOT(OnValueChangedZ(double)));
}


Vec3Widget::~Vec3Widget()
{
	delete m_layout;
}

void Vec3Widget::SetVec3(CloudMath::Vector3f& p_vector)
{
	if(!m_layout)
	{
		m_layout = new QGridLayout;
		m_layout->setSizeConstraint(QLayout::SetMinimumSize);
	}
	
	m_vector = p_vector;

 	m_xBox->SetValue(this->x());
	//m_xBox->SetLinkedVariable(&m_vector.x);
	m_layout->addWidget(m_xBox, 0, 0, Qt::AlignCenter);

	m_yBox->SetValue(this->y());
	//m_yBox->SetLinkedVariable(&m_vector.y);
	m_layout->addWidget(m_yBox, 0, 1, Qt::AlignCenter);

	m_zBox->SetValue(this->z());
	//m_zBox->SetLinkedVariable(&m_vector.z);
	m_layout->addWidget(m_zBox, 0, 2, Qt::AlignCenter);

	m_layout->setRowMinimumHeight(0, 30);

	this->setLayout(m_layout);
}


float Vec3Widget::x() const
{
	return m_vector.x;
}

float Vec3Widget::y() const
{
	return m_vector.y;
}

float Vec3Widget::z() const
{
	return m_vector.z;
}

void Vec3Widget::OnValueChangedX(double p_value)
{
	m_vector.x = p_value;
	emit ValueChangedFromVec3(m_vector);
}
void Vec3Widget::OnValueChangedY(double p_value)
{
	m_vector.y = p_value;
	emit ValueChangedFromVec3(m_vector );
}
void Vec3Widget::OnValueChangedZ(double p_value)
{
	m_vector.z = p_value;
	emit ValueChangedFromVec3(m_vector);
}