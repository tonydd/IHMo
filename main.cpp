#include "ihmo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IHMo w;

    // -- Text encoding
    //QTextCodec::setCodecForCStrings((QTextCodec::codecForName("UTF-8")));

    w.showMaximized();

    return a.exec();
}
