#include "AG2.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	AG2 w;
	w.show();
	return app.exec();
}