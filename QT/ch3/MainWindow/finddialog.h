#pragma once

#include <QDialog>
#include "FindDialog.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class FindDialog : public QDialog
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
    FindDialog(QWidget *parent = Q_NULLPTR);

};
