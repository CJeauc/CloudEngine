#pragma once

#include <QWidget>
#include "CloudMath/Vector/Vector3.h"
#include <QListView>

class QGridLayout;

namespace QtEditor
{
	class SmartLabelEdit;

	class Vec3Widget : public QWidget
	{
		Q_OBJECT
	public:
		Vec3Widget(const CloudMath::Vector3f& p_vector, QWidget *p_parent = nullptr);
		~Vec3Widget();

		void SetVec3(CloudMath::Vector3f& p_vector);

		float x() const;
		float y() const;
		float z() const;

	signals:
		void ValueChangedFromVec3(CloudMath::Vector3f p_vector);

	public slots:
		void OnValueChangedX(double p_value);
		void OnValueChangedY(double p_value);
		void OnValueChangedZ(double p_value);
		
	private:
		CloudMath::Vector3f		m_vector;
		QGridLayout*			m_layout;
		SmartLabelEdit*			m_xBox;
		SmartLabelEdit*			m_yBox;
		SmartLabelEdit*			m_zBox;

		float*					m_linkedX;
		float*					m_linkedY;
		float*					m_linkedZ;
	};
}

