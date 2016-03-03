#ifndef LINECOLLECTION_H
#define LINECOLLECTION_H

#include <QMutex>
#include <QSharedPointer>
#include <QVector>
#include "model/line.h"
#include "model/matrix.h"

namespace qst {

typedef QSharedPointer<Line> LinePointer;
typedef QVector<LinePointer> LineVector;

// Deletes: use std::swap and then pop_back vector.
class LineCollection
{
public:
    void add(float x, float y, float scalar, float decay, int maxlen, int tiplen);
    void decay();
    void endpoints(QVector<float> & xs, QVector<float> & ys, QVector<int> & ids);
    void extend(Vector2d & xs, Vector2d & ys,
                Vector2d & scalars, QVector<int> & ids);
    void lock();
    /* Remove dead lines. */
    void prune();
    const LineVector & getLines();
    void reset();
    QString str();
    void unlock();

private:
     LineVector mLines;
     QMutex mLock;
};

}

#endif
