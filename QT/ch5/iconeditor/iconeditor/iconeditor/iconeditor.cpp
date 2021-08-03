#include <QtGui>
#include <QPalette>
#include "iconeditor.h"

IconEditor::IconEditor(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    curColor = Qt::black;
    zoom = 8;
    image = QImage(16, 16, QImage::Format_ARGB32);
    image.fill(qRgba(0, 0, 0, 0));
}

QSize IconEditor::sizeHint()const
{
    QSize size = zoom * image.size();
    if (zoom >= 3)
        size += QSize(1, 1);
    return size;
}

void IconEditor::setPenColor(const QColor& newColor)
{
    curColor = newColor;
}

void IconEditor::setIconImage(const QImage& newImage)
{
    if (newImage != image) {
        image = newImage.convertToFormat(QImage::Format_ARGB32);
        update();
        updateGeometry();
    }
}

void IconEditor::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    if (zoom >= 3) {
        painter.setPen(*palette().WindowText());//这里书上有错误foreground被弃用，使用windowText()代替
    }
}