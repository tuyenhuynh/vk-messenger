#include "messenger.h"
#include <QtGui/QApplication>
#include <QTextCodec >
#include <json_parser.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Messenger w;

	QTextCodec *tc=QTextCodec::codecForName("CP1251");
	QTextCodec::setCodecForCStrings(tc);

    QTextCodec::setCodecForCStrings(tc);
    QTextCodec::setCodecForTr(tc);
    QTextCodec::setCodecForLocale(tc);

	w.show();
	return a.exec();
}
