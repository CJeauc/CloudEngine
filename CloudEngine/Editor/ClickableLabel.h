#pragma once

#include <QLabel>
#include <QWidget>
#include <Qt>

namespace QtEditor
{
	class ClickableLabel : public QLabel
	{
		Q_OBJECT
	public:
		explicit ClickableLabel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
		~ClickableLabel() = default;

		signals:
			void doubleClicked();

	protected:
		void mouseDoubleClickEvent(QMouseEvent* event) override;
	};
}