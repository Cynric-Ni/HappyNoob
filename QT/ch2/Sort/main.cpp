#include "SortDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SortDialog w;
    w.setColumnRange('C', 'F');
    w.show();
    return a.exec();
}
