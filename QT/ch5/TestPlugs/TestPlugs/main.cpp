#include "TestPlugs.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestPlugs w;
    w.show();
    return a.exec();
}
