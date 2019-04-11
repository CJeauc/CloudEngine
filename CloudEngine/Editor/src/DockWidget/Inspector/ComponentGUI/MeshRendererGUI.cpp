#include "stdafx.h"
#include "MeshRendererGUI.h"
#include "Core/CoreComponent/MeshRenderer.h"

#include <QApplication>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QDir>
#include <QDirIterator>
#include "Core/Managers/ResourceManager.h"

using namespace QtEditor;

MeshRendererGUI::MeshRendererGUI(const std::string& p_name, QWidget* p_parent)
	: AComponentGUI(p_name, p_parent), m_meshBox(new QComboBox(this)), m_meshComponent(nullptr)
{
	m_meshBox->setFixedSize(150, 25);

	QString path = QApplication::applicationDirPath() + "/../../../Resources/Model";
	QDir dir(path);
	QDirIterator it(path, QStringList() << "*.fbx" << "*.obj", QDir::Files, QDirIterator::Subdirectories);

	while (it.hasNext())
	{
		it.next();
		QString file = it.fileInfo().baseName();
		m_meshBox->addItem(file);
	}
	m_meshBox->addItem("Empty");
	connect(m_meshBox, SIGNAL(activated(QString)), this, SLOT(SetModel(QString)));
}

MeshRendererGUI::~MeshRendererGUI()
{
	delete m_meshBox;
}


void MeshRendererGUI::SetupFrame()
{
	if(m_meshComponent)
	{
		QLabel *label = new QLabel("Model",this);

		m_mainGridLayout->addWidget(label, 0, 0, Qt::AlignLeft);

		m_mainGridLayout->addWidget(m_meshBox, 0, 1, Qt::AlignCenter);
		m_mainGridLayout->setColumnStretch(1, 20);
	}
}

void MeshRendererGUI::BindComponent(std::shared_ptr<Core::AComponent> p_component)
{
	m_meshComponent = std::static_pointer_cast<Core::Components::MeshRenderer>(p_component);
	if(m_meshComponent->Model())
	{
		int index = m_meshBox->findText(m_meshComponent->Model()->Name().c_str());
		if (index != -1)
			m_meshBox->setCurrentIndex(index);
	}
	else if(!m_meshComponent->Model())
		m_meshBox->setCurrentText("Empty");
}

void MeshRendererGUI::SetModel(QString p_fileName) 
{
	m_meshComponent->SetModel(Cloud::Get().ResourceManager<Rendering::Model>()->GetResource(p_fileName.toStdString()));
}
