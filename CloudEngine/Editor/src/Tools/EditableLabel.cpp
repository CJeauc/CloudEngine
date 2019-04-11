#include "stdafx.h"
#include "EditableLabel.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QEvent>
#include <QKeyEvent>
using namespace QtEditor;

EditableLabel::EditableLabel(QWidget* p_parent)
	: QWidget(p_parent), m_goLabel(new ClickableLabel(this)), m_labelEditor(new QLineEdit(this))
{
	m_labelEditor->installEventFilter(this);

	connect(m_goLabel, SIGNAL(doubleClicked()), this, SLOT(RenameGameObject()));

	this->setStyleSheet("background-color: rgba(50,50,50,1); font-family : \"Dubai\"; font-size: 24px; padding 8px");
	m_labelEditor->setHidden(true);

	layout = new QHBoxLayout(this);

	layout->addWidget(m_goLabel);
	layout->addWidget(m_labelEditor);

	layout->setMargin(0);
	layout->setSpacing(0);

	this->setLayout(layout);
}

EditableLabel::~EditableLabel()
{
	m_goLabel->deleteLater();
	m_labelEditor->deleteLater();
	layout->deleteLater();
}

ClickableLabel* EditableLabel::GetLabel() const
{
	return m_goLabel;
}

QLineEdit* EditableLabel::GetLabelEditor() const
{
	return m_labelEditor;
}

void EditableLabel::RenameGameObject()
{
	m_goLabel->setHidden(true);
	m_labelEditor->setHidden(false);
}

bool EditableLabel::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == m_labelEditor)
	{
		if (event->type() == QEvent::KeyPress)
		{
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
			{
				emit nameChanged(m_labelEditor->text());
				emit nameChanged();
				m_labelEditor->clearFocus();
				m_goLabel->setText(m_labelEditor->text());
				m_goLabel->setHidden(false);
				m_labelEditor->setHidden(true);
				m_labelEditor->clear();
			}
		}
	}
	return QObject::eventFilter(obj, event);
}
