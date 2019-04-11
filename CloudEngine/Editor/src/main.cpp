
#include "Editor.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_UseStyleSheetPropagationInWidgetStyles, true);
	QApplication a(argc, argv);

	Editor w;
	w.show();
	return a.exec();
}