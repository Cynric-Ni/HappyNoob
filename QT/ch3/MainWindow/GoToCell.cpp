#include "GoToCell.h"
#include <QtGui>
#include <QtWidgets>
GoToCellDialog::GoToCellDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
   // buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    QRegularExpression regExp("[A-Za-z][1-9][0-9]{0,2}");
    lineEdit->setValidator(new QRegularExpressionValidator(regExp, this));

    connect(buttonBox, SIGNAL(clicked()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(clicked()), this, SLOT(reject()));
}

void GoToCellDialog::on_lineEdit_textChanged()
{
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(lineEdit->hasAcceptableInput());
}
