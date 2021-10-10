#include "plotter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Plotter w;
    w.show();
    return a.exec();
}
