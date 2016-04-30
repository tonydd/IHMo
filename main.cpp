#include "ihmo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IHMo w;
    w.show();

    return a.exec();
}
