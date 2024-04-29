#include "GameUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	GameUI w;
	w.show();
	return a.exec();
}
