#include "stdafx.h"
#include "Console.h"
#include <Tools/Event/Event.h>

#include <QContextMenuEvent>
#include <QBoxLayout>
#include <QLabel>
#include <QScrollBar>

using namespace QtEditor;

Console::Console(QWidget *parent)
	:QDockWidget("Console", parent)
{
	Debug::Log::s_useEvents = true;
	Debug::Log::m_event.AddListener(BIND(&Console::Print, this, HOLDER_1, HOLDER_2, HOLDER_3, HOLDER_4, HOLDER_5));

	this->setFocusPolicy(Qt::ClickFocus);
	this->setMinimumWidth(600);
	this->setMaximumWidth(650);

	setFeatures(QDockWidget::DockWidgetMovable  | QDockWidget::DockWidgetClosable);

	m_textEdit = new QTextEdit();
	m_textEdit->setReadOnly(true);

	this->setWidget(m_textEdit);
	this->widget()->setContentsMargins(0, 17, 0, 0);

	QScrollBar *sb = m_textEdit->verticalScrollBar();
	sb->setValue(sb->maximum());
}

void Console::focusInEvent(QFocusEvent* event)
{
	if (event->reason() == Qt::MouseFocusReason);
	{
		SLOG(Log::Debug(), "I'm in the console");
	}
}

void Console::Print(const std::string& p_message, const char* p_function, const char* p_file, int p_line,
	Debug::LogLevel p_level)
{
	m_textEdit->moveCursor(QTextCursor::End);
	QString message = QString::fromStdString(p_message + '\n');
	m_textEdit->setTextColor(QColor(201, 165, 37));
	m_textEdit->insertPlainText(message);
}
