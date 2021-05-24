#pragma once

#include <QtWidgets/QDialog>
#include "ui_find2.h"
class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class find2 : public QDialog
{
    Q_OBJECT
signals:
    void findNext(const QString& str, Qt::CaseSensitivity cs);
    void findPrevious(const QString& str, Qt::CaseSensitivity cs);
private slots:
    void findClicked();
    void enableFindButton(const QString& text);
private:
    QLabel* label;
    QLineEdit* lineEdit;
    QCheckBox* caseCheckBox;
    QCheckBox* backwardCheckBox;
    QPushButton* findButton;
    QPushButton* closeButton;
public:
    find2(QWidget *parent = Q_NULLPTR);

private:
    Ui::find2Class ui;
};
