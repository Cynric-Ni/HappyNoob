#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HelloQt.h"

class HelloQt : public QMainWindow
{
    Q_OBJECT

public:
    HelloQt(QWidget *parent = Q_NULLPTR);

private:
    Ui::HelloQtClass ui;
};
