#include "SortDialog.h"
#include <QtGui>
<<<<<<< HEAD
#include <QtCharts>
=======
//#include <QtCharts>
>>>>>>> 16e792ba6bff3e5de8650a9ade682ed65212a875
SortDialog::SortDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    ui.secondaryGroupBox->hide();
    ui.teriaryGroupBox->hide();
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    setColumnRange('A', 'Z');
}

void SortDialog::setColumnRange(QChar first,
    QChar last)
{
    ui.primaryColumnCombo->clear();
    ui.secondaryColumnCombo->clear();
    ui.tertiaryColumnCombo->clear();

    ui.secondaryColumnCombo->addItem(tr("None"));
    ui.tertiaryColumnCombo->addItem(tr("None"));
    ui.primaryColumnCombo->setMinimumSize(ui.secondaryColumnCombo->sizeHint());

    QChar ch = first;
    while (ch <= last) {
        ui.primaryColumnCombo->addItem(QString(ch));
        ui.secondaryColumnCombo->addItem(QString(ch));
        ui.tertiaryColumnCombo->addItem(QString(ch));
<<<<<<< HEAD
        //char16_t temp;
        ch = QChar(ch.unicode() + 1);
        //ch = QChar(temp);
=======
        ch = QChar((ch.unicode() + 1));
>>>>>>> 16e792ba6bff3e5de8650a9ade682ed65212a875
    }
}
