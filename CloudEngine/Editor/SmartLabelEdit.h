#pragma once
#pragma once

#include <QWidget>
#include <QDoubleValidator>
#include <SmartLabel.h>

class QLineEdit;

namespace QtEditor
{
	class SmartLabelEdit : public QWidget
	{
		Q_OBJECT
	public:
		SmartLabelEdit(const QString& p_label, QWidget* p_parent = nullptr);
		SmartLabelEdit(SmartLabel* p_label, QWidget* p_parent = nullptr);

		void		SetMultiplier(double p_multiplier);
		void		SetValue(double p_value);
		void		SetMinValue(double p_value);
		void		SetMaxValue(double p_value);
		void		SetLinkedVariable(const float* p_variable);
		SmartLabel*	GetLabel();
		bool		FieldHasFocus();
		double		GetValue() const;

	signals:
		void ValueChanged(double p_value);

	public slots:
		void DragStarted(QMouseEvent* event);
		void Dragged(QMouseEvent* event);
		void DragStopped(QMouseEvent* event);
		void FieldChanged(const QString text);

	protected:
		void Setup();
		bool eventFilter(QObject* obj, QEvent *event);
		void paintEvent(QPaintEvent* event) override;

	protected:
		QLineEdit*			m_field;
		SmartLabel*			m_label;
		QDoubleValidator*	m_validator;
		double				m_mouseStartPosX{ 0 };
		double				m_multiplier{ 200 };
		const float*		m_linkedVariable{ nullptr };
	};
}