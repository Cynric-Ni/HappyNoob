#include "HelloQt.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qslider.h>
#include <QtWidgets/qspinbox.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*¼ÇºÅ1QLabel* label = new QLabel("<h2><i>Hello</i><font color=red> QT!</font></h2>");
    label->show();
    QPushButton* button = new QPushButton("Quit");
    QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));
    button->show();*/

    QWidget* window = new QWidget;
    window->setWindowTitle("Enter Your Age");

    QSpinBox *spinBox = new QSpinBox;
    QSlider* slider = new QSlider(Qt::Horizontal);
    spinBox->setRange(0, 130);
    slider->setRange(0, 130);

    QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));

    spinBox->setValue(35);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(spinBox);
    layout->addWidget(slider);
    window->setLayout(layout);

    window->show();
    return a.exec();
}
