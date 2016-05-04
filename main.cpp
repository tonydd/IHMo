#include "ihmo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IHMo w;

    // -- Text encoding
    QTextCodec::setCodecForCStrings((QTextCodec::codecForName("UTF-8")));

    w.show();

    return a.exec();
}
