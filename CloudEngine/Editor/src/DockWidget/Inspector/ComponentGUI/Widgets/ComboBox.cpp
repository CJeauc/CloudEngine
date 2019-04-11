#include "stdafx.h"
#include "ComboxBox.h"

#include <QComboBox>
#include <Qstring>
#include <QStringList>
#include <QDir>
#include <QDirIterator>
#include <QApplication>

using namespace QtEditor;

ComboBoxCustom::ComboBoxCustom(const QString& p_path, const QStringList& p_filter, QWidget* p_parent)
	: QWidget(p_parent), m_box(new QComboBox(p_parent))
{
	m_box->setFixedSize(150, 25);

	QString path = QApplication::applicationDirPath() + p_path;
	QDir dir(path);
	QDirIterator it(path, p_filter, QDir::Files, QDirIterator::Subdirectories);

	while (it.hasNext())
	{
		it.next();
		QString file = it.fileInfo().baseName();
		m_box->addItem(file);
	}
}

ComboBoxCustom::~ComboBoxCustom()
{
	delete m_box;
}

QComboBox* ComboBoxCustom::GetBox() const
{
	return m_box;
}