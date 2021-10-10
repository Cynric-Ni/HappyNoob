#pragma once

#include <QMap>
#include <QPixmap>
#include <QVector>
#include <QtWidgets/QWidget>
#include <QToolButton>
#include "ui_plotter.h"

class QToolButton;
class PlotSettings;

class Plotter : public QWidget
{
    Q_OBJECT

public:
    Plotter(QWidget *parent = Q_NULLPTR);
    void setPlotSettings(const PlotSettings & settings);
    void setCurveData(int id, const QVector<QPointF>& data);
    void clearCure(int id);
    QSize minimumSizeHint()const;
    QSize sizeHint()const;

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void wheelEvent(QWheelEvent* event);

private:
    void updateRubberBandRegion();
    void refreshPixmap();
    void drawCurves(QPainter* painter);
    void drawCurves(QPainter* painter);

    enum{Margin = 50};

    QToolButton* zoomInButton;
    QToolButton* zoomOutButton;
    QMap<int, QVector<QPointF>>curveMap;
    QVector<PlotSettings> zoomStack;
    int curZoom;
    bool rubberBandIsShown;
    QRect rubberBandRect;
    QPixmap pixmap;
    //Ui::PlotterClass ui;
};
