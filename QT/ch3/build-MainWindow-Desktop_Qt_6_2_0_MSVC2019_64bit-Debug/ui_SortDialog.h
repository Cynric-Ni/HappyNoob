/********************************************************************************
** Form generated from reading UI file 'SortDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SORTDIALOG_H
#define UI_SORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_SortDialog
{
public:
    QGridLayout *gridLayout_4;
    QPushButton *okButton;
    QSpacerItem *verticalSpacer;
    QGroupBox *secondaryGroupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *secondaryColumnCombo;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *comboBox_4;
    QGroupBox *teriaryGroupBox;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QComboBox *tertiaryColumnCombo;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *comboBox_6;
    QLabel *label_6;
    QGroupBox *primaryGroupBox;
    QGridLayout *gridLayout;
    QComboBox *primaryColumnCombo;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QPushButton *cancelButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *moreButton;

    void setupUi(QDialog *SortDialog)
    {
        if (SortDialog->objectName().isEmpty())
            SortDialog->setObjectName(QString::fromUtf8("SortDialog"));
        SortDialog->resize(297, 316);
        gridLayout_4 = new QGridLayout(SortDialog);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        okButton = new QPushButton(SortDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        gridLayout_4->addWidget(okButton, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 4, 0, 1, 1);

        secondaryGroupBox = new QGroupBox(SortDialog);
        secondaryGroupBox->setObjectName(QString::fromUtf8("secondaryGroupBox"));
        gridLayout_2 = new QGridLayout(secondaryGroupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_3 = new QLabel(secondaryGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        label_4 = new QLabel(secondaryGroupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        secondaryColumnCombo = new QComboBox(secondaryGroupBox);
        secondaryColumnCombo->addItem(QString());
        secondaryColumnCombo->setObjectName(QString::fromUtf8("secondaryColumnCombo"));

        gridLayout_2->addWidget(secondaryColumnCombo, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        comboBox_4 = new QComboBox(secondaryGroupBox);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));

        gridLayout_2->addWidget(comboBox_4, 1, 1, 1, 2);


        gridLayout_4->addWidget(secondaryGroupBox, 5, 0, 1, 1);

        teriaryGroupBox = new QGroupBox(SortDialog);
        teriaryGroupBox->setObjectName(QString::fromUtf8("teriaryGroupBox"));
        gridLayout_3 = new QGridLayout(teriaryGroupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_5 = new QLabel(teriaryGroupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 1, 0, 1, 1);

        tertiaryColumnCombo = new QComboBox(teriaryGroupBox);
        tertiaryColumnCombo->addItem(QString());
        tertiaryColumnCombo->setObjectName(QString::fromUtf8("tertiaryColumnCombo"));

        gridLayout_3->addWidget(tertiaryColumnCombo, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        comboBox_6 = new QComboBox(teriaryGroupBox);
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));

        gridLayout_3->addWidget(comboBox_6, 1, 1, 1, 2);

        label_6 = new QLabel(teriaryGroupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);


        gridLayout_4->addWidget(teriaryGroupBox, 6, 0, 1, 1);

        primaryGroupBox = new QGroupBox(SortDialog);
        primaryGroupBox->setObjectName(QString::fromUtf8("primaryGroupBox"));
        gridLayout = new QGridLayout(primaryGroupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        primaryColumnCombo = new QComboBox(primaryGroupBox);
        primaryColumnCombo->addItem(QString());
        primaryColumnCombo->setObjectName(QString::fromUtf8("primaryColumnCombo"));

        gridLayout->addWidget(primaryColumnCombo, 0, 1, 1, 1);

        label_2 = new QLabel(primaryGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        comboBox_2 = new QComboBox(primaryGroupBox);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 1, 1, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        label = new QLabel(primaryGroupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        gridLayout_4->addWidget(primaryGroupBox, 0, 0, 3, 1);

        cancelButton = new QPushButton(SortDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        gridLayout_4->addWidget(cancelButton, 1, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_2, 2, 1, 1, 1);

        moreButton = new QPushButton(SortDialog);
        moreButton->setObjectName(QString::fromUtf8("moreButton"));
        moreButton->setCheckable(true);

        gridLayout_4->addWidget(moreButton, 4, 1, 1, 1);

        QWidget::setTabOrder(primaryColumnCombo, comboBox_2);
        QWidget::setTabOrder(comboBox_2, secondaryColumnCombo);
        QWidget::setTabOrder(secondaryColumnCombo, comboBox_4);
        QWidget::setTabOrder(comboBox_4, tertiaryColumnCombo);
        QWidget::setTabOrder(tertiaryColumnCombo, comboBox_6);
        QWidget::setTabOrder(comboBox_6, okButton);

        retranslateUi(SortDialog);
        QObject::connect(okButton, &QPushButton::clicked, SortDialog, qOverload<>(&QDialog::accept));
        QObject::connect(cancelButton, &QPushButton::clicked, SortDialog, qOverload<>(&QDialog::reject));
        QObject::connect(moreButton, &QPushButton::toggled, secondaryGroupBox, &QGroupBox::setVisible);
        QObject::connect(moreButton, &QPushButton::toggled, teriaryGroupBox, &QGroupBox::setVisible);

        okButton->setDefault(true);


        QMetaObject::connectSlotsByName(SortDialog);
    } // setupUi

    void retranslateUi(QDialog *SortDialog)
    {
        SortDialog->setWindowTitle(QCoreApplication::translate("SortDialog", "SortDialog", nullptr));
        okButton->setText(QCoreApplication::translate("SortDialog", "OK", nullptr));
        secondaryGroupBox->setTitle(QCoreApplication::translate("SortDialog", "&Secondary Key", nullptr));
        label_3->setText(QCoreApplication::translate("SortDialog", "Order", nullptr));
        label_4->setText(QCoreApplication::translate("SortDialog", "Column", nullptr));
        secondaryColumnCombo->setItemText(0, QCoreApplication::translate("SortDialog", "None", nullptr));

        comboBox_4->setItemText(0, QCoreApplication::translate("SortDialog", "Ascending", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("SortDialog", "Descending", nullptr));

        teriaryGroupBox->setTitle(QCoreApplication::translate("SortDialog", "&Teritary Key", nullptr));
        label_5->setText(QCoreApplication::translate("SortDialog", "Order", nullptr));
        tertiaryColumnCombo->setItemText(0, QCoreApplication::translate("SortDialog", "None", nullptr));

        comboBox_6->setItemText(0, QCoreApplication::translate("SortDialog", "Ascending", nullptr));
        comboBox_6->setItemText(1, QCoreApplication::translate("SortDialog", "Descending", nullptr));

        label_6->setText(QCoreApplication::translate("SortDialog", "Column", nullptr));
        primaryGroupBox->setTitle(QCoreApplication::translate("SortDialog", "&Primary Key", nullptr));
        primaryColumnCombo->setItemText(0, QCoreApplication::translate("SortDialog", "None", nullptr));

        label_2->setText(QCoreApplication::translate("SortDialog", "Order", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("SortDialog", "Ascending", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("SortDialog", "Descending", nullptr));

        label->setText(QCoreApplication::translate("SortDialog", "Column", nullptr));
        cancelButton->setText(QCoreApplication::translate("SortDialog", "Cancel", nullptr));
        moreButton->setText(QCoreApplication::translate("SortDialog", "&More", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SortDialog: public Ui_SortDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SORTDIALOG_H
