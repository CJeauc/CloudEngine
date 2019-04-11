#include "stdafx.h"
#include "ClickableLabel.h"
using namespace QtEditor;

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
	:QLabel(parent)
{
}

void ClickableLabel::mouseDoubleClickEvent(QMouseEvent* event)
{
	emit doubleClicked();

}
