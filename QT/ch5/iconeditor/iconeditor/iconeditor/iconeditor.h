#pragma once

#include <QtWidgets/QWidget>
#include <QColor>
#include <QImage>

class iconeditor : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage)
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)

public:
    iconeditor(QWidget *parent = Q_NULLPTR);

    void setPenColor(const QColor& newColor);
    QColor penColor() const { return curColor; }

private:


    QColor curColor;
    QImage image;
    int zoom;
};
