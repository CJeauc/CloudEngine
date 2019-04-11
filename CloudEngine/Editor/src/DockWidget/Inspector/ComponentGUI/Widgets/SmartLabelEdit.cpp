#include "stdafx.h"
#include "SmartLabelEdit.h"

#include <QLineEdit>
#include <QApplication>
#include <QDesktopWidget>
#include <QLocale>
#include <QHBoxLayout>
#include <QKeyEvent>

using namespace QtEditor;

SmartLabelEdit::SmartLabelEdit(const QString& p_label, QWidget* p_parent)
	: QWidget(p_parent), m_label(new SmartLabel(p_label)), m_field(new QLineEdit("0.000"))
{
	Setup();
}

SmartLabelEdit::SmartLabelEdit(SmartLabel* p_label, QWidget* p_parent)
	: QWidget(p_parent), m_label(p_label), m_field(new QLineEdit("0.000"))
{
	Setup();
}

void SmartLabelEdit::SetMultiplier(double p_multiplier)
{
	m_multiplier = p_multiplier;
}

void SmartLabelEdit::SetValue(double p_value)
{
	m_field->setText(QString::number(p_value, 'g', 4));
}

void SmartLabelEdit::SetMinValue(double p_value)
{
	m_validator->setBottom(p_value);
}

void SmartLabelEdit::SetMaxValue(double p_value)
{
	m_validator->setTop(p_value);
}

void SmartLabelEdit::SetLinkedVariable(const float* p_variable)
{
	m_linkedVariable = p_variable;
}

SmartLabel* SmartLabelEdit::GetLabel()
{
	return m_label;
}

bool SmartLabelEdit::FieldHasFocus()
{
	return m_field->hasFocus();
}

double SmartLabelEdit::GetValue() const
{
	return m_field->text().toDouble();
}

void SmartLabelEdit::DragStarted(QMouseEvent* event)
{
	m_mouseStartPosX = QCursor::pos().x();
}

void SmartLabelEdit::Dragged(QMouseEvent* event)
{
	QRect rec = QApplication::desktop()->screenGeometry();

	double valueOffset = (QCursor::pos().x() - m_mouseStartPosX) / rec.width() * m_multiplier;
	double x = m_field->text().toDouble();
	double newValue = m_field->text().toDouble() + valueOffset;
	if (newValue <= m_validator->top() && newValue > m_validator->bottom())
		m_field->setText(QString::number(newValue, 'g', 4));

	emit ValueChanged(m_field->text().toDouble());

	if (QCursor::pos().x() >= rec.width() - 1)
		cursor().setPos(1, QCursor::pos().y());
	if (QCursor::pos().x() <= 0)
		cursor().setPos(QCursor::pos().x() + rec.width(), QCursor::pos().y());

	m_mouseStartPosX = QCursor::pos().x();
}

void SmartLabelEdit::DragStopped(QMouseEvent* event)
{
	emit ValueChanged(m_field->text().toDouble());
}

void SmartLabelEdit::FieldChanged(const QString text)
{
	emit ValueChanged(text.toDouble());
}

void SmartLabelEdit::Setup()
{
	this->setStyleSheet("QLineEdit {font-size: 12px; background-color: rgba(0,0,0,1)}; border : 1px solid gray;");
	QLocale loc(QLocale::C);
	loc.setNumberOptions(QLocale::RejectGroupSeparator);

	m_validator = new QDoubleValidator(this);
	m_validator->setLocale(loc);
	m_validator->setDecimals(4);

	m_field->setValidator(m_validator);

	m_field->setMinimumWidth(40);
	m_field->setFixedHeight(20);

	m_field->setAlignment(Qt::AlignRight);
	m_field->installEventFilter(this);

	QHBoxLayout* layout = new QHBoxLayout;
	layout->setSpacing(5);
	layout->setMargin(3);

	layout->addWidget(m_label, 0, Qt::AlignRight);
	layout->addWidget(m_field, 1, Qt::AlignLeft);
	setLayout(layout);

	connect(m_label, SIGNAL(DragStart(QMouseEvent*)), this, SLOT(DragStarted(QMouseEvent*)));
	connect(m_label, SIGNAL(Drag(QMouseEvent*)), this, SLOT(Dragged(QMouseEvent*)));
	connect(m_label, SIGNAL(DragStop(QMouseEvent*)), this, SLOT(DragStopped(QMouseEvent*)));
}

bool SmartLabelEdit::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == m_field)
	{
		if (event->type() == QEvent::FocusAboutToChange)
			emit ValueChanged(m_field->text().toDouble());
		else if (event->type() == QEvent::KeyPress)
		{
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
			{
				emit ValueChanged(m_field->text().toDouble());
				m_field->clearFocus();
			}
		}
	}
	return QObject::eventFilter(obj, event);
}

void SmartLabelEdit::paintEvent(QPaintEvent* event)
{
	if (m_linkedVariable && *m_linkedVariable != m_field->text().toDouble() && !m_field->hasFocus())
		m_field->setText(QString::number(*m_linkedVariable, 'g', 4));

	QWidget::paintEvent(event);
}

