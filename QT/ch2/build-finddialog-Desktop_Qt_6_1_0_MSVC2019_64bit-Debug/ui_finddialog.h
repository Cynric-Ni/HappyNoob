/********************************************************************************
** Form generated from reading UI file 'finddialog.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDDIALOG_H
#define UI_FINDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_finddialogClass
{
public:

    void setupUi(QDialog *finddialogClass)
    {
        if (finddialogClass->objectName().isEmpty())
            finddialogClass->setObjectName(QString::fromUtf8("finddialogClass"));
        finddialogClass->resize(600, 400);

        retranslateUi(finddialogClass);

        QMetaObject::connectSlotsByName(finddialogClass);
    } // setupUi

    void retranslateUi(QDialog *finddialogClass)
    {
        finddialogClass->setWindowTitle(QCoreApplication::translate("finddialogClass", "finddialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class finddialogClass: public Ui_finddialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDDIALOG_H
