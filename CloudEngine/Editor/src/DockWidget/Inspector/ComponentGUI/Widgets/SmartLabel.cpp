#include "stdafx.h"
#include "SmartLabel.h"

#include <QMouseEvent>

using namespace QtEditor;

SmartLabel::SmartLabel(const QString& p_label, QWidget* p_parent)
	:QLabel(p_label, p_parent)
{
	this->setFixedHeight(20);
}


void SmartLabel::mousePressEvent(QMouseEvent* event)
{
	emit DragStart(event);
}

void SmartLabel::mouseMoveEvent(QMouseEvent* event)
{
	emit Drag(event);
}

void SmartLabel::mouseReleaseEvent(QMouseEvent* event)
{
	emit DragStop(event);
}

void SmartLabel::enterEvent(QEvent* event)
{
	setCursor(QCursor(Qt::SizeHorCursor));
}

void SmartLabel::leaveEvent(QEvent* event)
{
	setCursor(QCursor(Qt::ArrowCursor));
}
