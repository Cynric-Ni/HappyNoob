#include "HelloQt.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //HelloQt w;
    //w.show();
    QLabel* label = new QLabel("<h2><i>Hello</i><font color=red> QT!</font></h2>");
    label->show();
    QPushButton* button = new QPushButton("Quit");
    QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));
    button->show();
    return a.exec();
}
