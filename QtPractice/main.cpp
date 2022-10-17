#include "custom_test.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	CustomTest w;
	QString qss_file = ":/new/prefix1/StyleSheet.css";
	QFile file(qss_file);
	if (file.open(QFile::ReadOnly))
	{
		QString styleSheet = QString::fromLatin1(file.readAll());
		a.setStyleSheet(styleSheet);
	}

	return a.exec();
}