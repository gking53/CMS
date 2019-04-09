#include "CMSGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CMSGUI w;
	w.show();
	return a.exec();
}
