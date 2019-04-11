#pragma once
#include <QPushButton>
#include <QTreeWidget>

namespace QtEditor
{
	class Category : public QPushButton
	{
		Q_OBJECT
	public:
		Category(QTreeWidget* p_parent, const QString& p_text, QTreeWidgetItem* p_item);

	private slots:
		void ButtonPressed();

	private:
		QTreeWidgetItem* m_item;
	};
}