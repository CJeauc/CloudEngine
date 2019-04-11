#pragma once
#include <QMessageBox>

class QLabel;
class QPushButton;

namespace QtEditor
{
	class NotificationsBox : public QMessageBox
	{
		Q_OBJECT
	public:
		explicit NotificationsBox(QWidget *parent = nullptr);
		~NotificationsBox();

		char SaveNotifications(QString& p_sceneName);

	};
}
