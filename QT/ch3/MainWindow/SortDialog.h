#pragma once

#include <QtWidgets/QDialog>
#include "ui_SortDialog.h"

class SortDialog : public QDialog,public Ui::SortDialog
{
    Q_OBJECT

public:
    SortDialog(QWidget *parent = Q_NULLPTR);
    void setColumnRange(QChar first, QChar last);
};
