#include "stdafx.h"
#include "NotificationsBox.h"

#include <QPushButton>
#include <QHBoxLayout>


using namespace QtEditor;

NotificationsBox::NotificationsBox(QWidget* parent)
	: QMessageBox(parent)
{}

NotificationsBox::~NotificationsBox()
{}

char NotificationsBox::SaveNotifications(QString& p_sceneName)
{
	this->setObjectName("SaveBox");

	QString it("Unsave changes on scene : " + p_sceneName);
	setWindowFlags(Qt::Window |Qt::FramelessWindowHint);
	setText(it);

	setStandardButtons(QMessageBox::Save | QMessageBox::Ignore |QMessageBox::Cancel);
	setDefaultButton(QMessageBox::Cancel);

	int ret = this->exec();
	
	if (ret == QMessageBox::Save)
		return 1;
	if (ret == QMessageBox::Ignore)
		return 0;
	if (ret == QMessageBox::Cancel)
		return -1;
}
