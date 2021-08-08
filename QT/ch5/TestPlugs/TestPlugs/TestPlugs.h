#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TestPlugs.h"

class TestPlugs : public QMainWindow
{
    Q_OBJECT

public:
    TestPlugs(QWidget *parent = Q_NULLPTR);

private:
    Ui::TestPlugsClass ui;
};
