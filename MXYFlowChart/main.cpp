#include "flowchar_widget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FlowCharWidget flowchar_widget;
	flowchar_widget.show();
	return a.exec();
}
