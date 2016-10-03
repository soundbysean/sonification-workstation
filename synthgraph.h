#ifndef SYNTHGRAPH_H
#define SYNTHGRAPH_H

#include <QObject>
#include <QVector>
#include <synthitem.h>
#include <output.h>
#include "oscillator.h"

namespace son {

class SynthGraph : public QObject
{
    Q_OBJECT
public:

    enum SynthItemType {
        OUT,
        OSCILLATOR
    };

    Q_ENUM(SynthItemType)

    explicit SynthGraph(QObject *parent = 0);

    Q_INVOKABLE QObject* createItem(QObject *gui, int type);
    Q_INVOKABLE void addToRoot(SynthItem* synthItem);
    Q_INVOKABLE void removeFromRoot(SynthItem* synthItem);

    float processGraph();
    int graphSize();

signals:

public slots:


private:
    QVector<SynthItem*> graphRoot;

};

} //namespace son

#endif // SYNTHGRAPH_H
