#pragma once
#include <QtWidgets/QDialog>
#include "ui_GoToCell.h"
class GoToCellDialog : public QDialog,public Ui::GoToCellDialog
{
    Q_OBJECT

public:
    GoToCellDialog(QWidget *parent = Q_NULLPTR);

private slots:
    void on_lineEdit_textChanged();
};
