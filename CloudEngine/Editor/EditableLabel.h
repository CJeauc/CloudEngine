#pragma once
#include <QWidget>
#include "ClickableLabel.h"

class QLineEdit;
class QHBoxLayout;

namespace QtEditor
{
	class EditableLabel : public QWidget
	{
		Q_OBJECT
	public:
		EditableLabel(QWidget *p_parent = nullptr);
		~EditableLabel();

		ClickableLabel* GetLabel() const;
		QLineEdit*  GetLabelEditor() const;

	protected:
		bool eventFilter(QObject* obj, QEvent* event) override;

	private slots:
		void RenameGameObject();
	signals:
		void nameChanged(const QString& p_name);
		void nameChanged();

	private:
		ClickableLabel	*m_goLabel;
		QLineEdit		*m_labelEditor;
		QHBoxLayout		*layout;
	};
}