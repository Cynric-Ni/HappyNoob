/********************************************************************************
** Form generated from reading UI file 'plotter.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTTER_H
#define UI_PLOTTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlotterClass
{
public:

    void setupUi(QWidget *PlotterClass)
    {
        if (PlotterClass->objectName().isEmpty())
            PlotterClass->setObjectName(QString::fromUtf8("PlotterClass"));
        PlotterClass->resize(600, 400);

        retranslateUi(PlotterClass);

        QMetaObject::connectSlotsByName(PlotterClass);
    } // setupUi

    void retranslateUi(QWidget *PlotterClass)
    {
        PlotterClass->setWindowTitle(QCoreApplication::translate("PlotterClass", "Plotter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlotterClass: public Ui_PlotterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTTER_H
