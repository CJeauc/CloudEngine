/********************************************************************************
** Form generated from reading UI file 'Editor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOR_H
#define UI_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditorClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *AssetBrowserSplit;
    QTreeView *DirectoriesTree;
    QListView *listView;
    QTreeView *Hierarchy;
    QSplitter *splitter;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSplitter *MainFrameSplitter;
    QTreeWidget *Inspector;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *EditorClass)
    {
        if (EditorClass->objectName().isEmpty())
            EditorClass->setObjectName(QString::fromUtf8("EditorClass"));
        EditorClass->resize(1928, 1080);
        QPalette palette;
        QBrush brush(QColor(163, 166, 166, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(20, 20, 20, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush2(QColor(163, 166, 166, 128));
        brush2.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush3(QColor(163, 166, 166, 128));
        brush3.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush4(QColor(163, 166, 166, 128));
        brush4.setStyle(Qt::NoBrush);
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush4);
        EditorClass->setPalette(palette);
        EditorClass->setStyleSheet(QString::fromUtf8("*\n"
"{\n"
"border: none; \n"
"color: #A3A6A6;\n"
"font-family: \"Dubai\";\n"
"font-size: 16px;\n"
"titlebar-close-icon: url(Resources/closeButton.png);\n"
"titlebar-normal-icon: url(Resources/Capture.png)\n"
"}\n"
"\n"
"QMainWindow, QSplitter\n"
"{\n"
"background-color: #141414; \n"
"}\n"
"\n"
"QDockWidget::title\n"
"{\n"
"	height: 16px;\n"
"	padding: 3px 9px;\n"
"}\n"
"QDockWidget, QTreeView, QListView\n"
"{\n"
"background-color: #323232;\n"
"}\n"
"\n"
"QSplitter#AssetBrowserSplit::handle\n"
"{\n"
"background-color: #181818;\n"
"padding: 0 3px;\n"
"}\n"
"\n"
"QTreeView#DirectoriesTree\n"
"{\n"
"	margin-right: 0;\n"
"}\n"
"\n"
"QListView#ListView\n"
"{\n"
"	margin-left: 0;\n"
"}\n"
"\n"
"QDockWidget QTextEdit\n"
"{\n"
"	font-size: 14px;\n"
"}\n"
"\n"
"QDockWidget::close-button, QDockWidget::float-button\n"
"{\n"
"	border: 1px transparent;	\n"
"	padding: 0px;\n"
"}\n"
"\n"
"QMenuBar\n"
"{\n"
"	background-color: #323232;\n"
"	border: 1px solid black;\n"
"}\n"
"\n"
"QMenuBar::item\n"
"{\n"
"padding: 8px;\n"
"hei"
                        "ght: 30px;\n"
"}\n"
"\n"
"QMenuBar::item:selected\n"
"{\n"
"	background-color: rgba(255, 255, 255, 0.1);\n"
"}\n"
"\n"
"QMenu:active\n"
"{\n"
"	padding : 0;\n"
"	margin : 0;\n"
"}\n"
"\n"
"QMenu::item\n"
"{\n"
"	margin : 0;\n"
"	background-color: #252526;\n"
"	padding: 3px 25px;\n"
"}\n"
"\n"
"QMenu::item::selected\n"
"{\n"
"	margin: 0px;\n"
"	background-color:  rgba(255, 255, 255, 0.1);\n"
"	border-color: darkblue;\n"
"}\n"
"\n"
"QMenu::separator\n"
"{\n"
"	height: 2px;\n"
"	background: #323232;\n"
"}\n"
"\n"
"QMessageBox#SaveBox\n"
"{	\n"
"	min-width: 1000px;\n"
"	background-color:#141414;\n"
"}\n"
"\n"
"QMessageBox#SaveBox QPushButton\n"
"{\n"
"	padding: 0 12px 0px 12px;\n"
"	margin: 0 6px;\n"
"	background-color:  #282828;\n"
"}\n"
"\n"
"QMessageBox#SaveBox QPushButton::hover\n"
"{\n"
"	background-color : rgba(255,255,255, 0.1);\n"
"	border-color: darkblue\n"
"}\n"
"\n"
""));
        centralWidget = new QWidget(EditorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        AssetBrowserSplit = new QSplitter(centralWidget);
        AssetBrowserSplit->setObjectName(QString::fromUtf8("AssetBrowserSplit"));
        AssetBrowserSplit->setOrientation(Qt::Horizontal);
        DirectoriesTree = new QTreeView(AssetBrowserSplit);
        DirectoriesTree->setObjectName(QString::fromUtf8("DirectoriesTree"));
        AssetBrowserSplit->addWidget(DirectoriesTree);
        listView = new QListView(AssetBrowserSplit);
        listView->setObjectName(QString::fromUtf8("listView"));
        AssetBrowserSplit->addWidget(listView);

        gridLayout->addWidget(AssetBrowserSplit, 3, 0, 1, 1);

        Hierarchy = new QTreeView(centralWidget);
        Hierarchy->setObjectName(QString::fromUtf8("Hierarchy"));

        gridLayout->addWidget(Hierarchy, 2, 0, 1, 1);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        frame = new QFrame(splitter);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        MainFrameSplitter = new QSplitter(frame);
        MainFrameSplitter->setObjectName(QString::fromUtf8("MainFrameSplitter"));
        MainFrameSplitter->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(MainFrameSplitter);

        splitter->addWidget(frame);

        gridLayout->addWidget(splitter, 1, 0, 1, 1);

        Inspector = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        Inspector->setHeaderItem(__qtreewidgetitem);
        Inspector->setObjectName(QString::fromUtf8("Inspector"));
        Inspector->setRootIsDecorated(false);
        Inspector->header()->setVisible(false);

        gridLayout->addWidget(Inspector, 2, 1, 2, 1);

        EditorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(EditorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        EditorClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(EditorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1928, 46));
        EditorClass->setMenuBar(menuBar);

        retranslateUi(EditorClass);

        QMetaObject::connectSlotsByName(EditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditorClass)
    {
        EditorClass->setWindowTitle(QApplication::translate("EditorClass", "Editor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditorClass: public Ui_EditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
