#include "finddialog.h"
#include <QtGui>
#include <QtWidgets>
finddialog::finddialog(QWidget *parent)
    : QDialog(parent)
{
    label = new QLabel(tr("Find&what:"));
    ui.setupUi(this);
}
