#pragma once

#include <QtWidgets/QDialog>
#include "ui_finddialog.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class finddialog : public QDialog
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
    finddialog(QWidget *parent = Q_NULLPTR);

private:
    Ui::finddialogClass ui;
};
