#pragma once
#include <QWidget>

class QComboBox;
class QString;
class QStringList;

namespace QtEditor
{
	class ComboBoxCustom : public QWidget
	{
		Q_OBJECT
	public:
		ComboBoxCustom(const QString& p_path, const QStringList& p_filter, QWidget *p_parent = nullptr);
		~ComboBoxCustom();

		QComboBox* GetBox() const ;
	private:
		QComboBox	*m_box;
	};

	
}
