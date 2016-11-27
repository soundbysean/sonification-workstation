#ifndef SCATTERVIEW_H
#define SCATTERVIEW_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QHXYModelMapper>
#include <QPen>
#include <qmath.h>

#include "tablemodel.h"
#include "sequencer.h"

QT_CHARTS_USE_NAMESPACE

namespace son {

class ScatterView: public QChartView
{
    Q_OBJECT

public:
    ScatterView(QWidget* parent = 0);
    ~ScatterView();
    void mouseMoveEvent(QMouseEvent* event);
    void setModel(QAbstractItemModel *m, int xRow = 0, int yRow = 1);
    void setSequencer(Sequencer * const seq);

private slots:
    void handleMouseMoved(const QPointF &point);

private:

    QChart* scatterChart;
    QHXYModelMapper* mapper;
    QAbstractItemModel* model;
    QScatterSeries* scatterSeries;
    QScatterSeries* triggeredSeries;
    QPen* scatterPen;
    QPen* triggeredPen;
    QHash<QString, int>* hashTable;

    Sequencer* sequencer;

    void triggerPoint(QPointF point);

};

}

#endif // CHARTVIEW_H