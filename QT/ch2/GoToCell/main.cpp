#include "GoToCell.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
    //GoToCellDialog changeUi;
    GoToCellDialog* dialog = new GoToCellDialog;
    //changeUi.setupUi(dialog);
        dialog->show();
     //GoToCell w;
    //w.show();
    return a.exec();
}
