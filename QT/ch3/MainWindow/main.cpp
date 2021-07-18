#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qsplashscreen.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // QSplashScreen* splash = new QSplashScreen;
   // splash->setPixmap(QPixmap("../Image/wenhao.png"));
   // splash->show();

  //  Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
   // splash->showMessage(QObject::tr("Setting up the main window..."),
   //     topRight, Qt::white);
    MainWindow w;

    //splash->showMessage(QObject::tr("Loading modules..."),
  //      topRight, Qt::white);
    //loadModules();

  //  splash->showMessage(QObject::tr("Establishing connections..."),
   //     topRight, Qt::white);
    //establishConnections();
    w.show();
    //splash->finish(&w);
   // delete splash;

    return a.exec();
}
