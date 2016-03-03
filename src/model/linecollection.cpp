#include "linecollection.h"
#include <QDebug>

namespace qst {

void LineCollection::add(float x, float y, float scalar,
                         float decay, int maxlen, int tiplen)
{
    QSharedPointer<Line> line(new Line(decay, maxlen, tiplen));
    line->extend(x, y, scalar);
    mLines.push_back(line);
}

void LineCollection::decay()
{
    int n = mLines.size();
    for(int i = 0; i < n; ++i)
    {
        mLines[i]->decay();
    }
}

void LineCollection::endpoints(QVector<float> & xs, QVector<float> & ys,
                               QVector<int> & ids)
{
    int n = mLines.size();
    ids.clear();
    xs.clear();
    ys.clear();

    for(int i = 0; i < n; ++i)
    {
        QSharedPointer<Line> & line = mLines[i];
        if (line->extendable()) {
            ids.push_back(i);
            float x = line->lastX();
            float y = line->lastY();
            xs.push_back(x);
            ys.push_back(y);
        }
    }
}

void LineCollection::extend(
        Vector2d & xs, Vector2d & ys, Vector2d & scalars,
        QVector<int> & ids)
{
    int n = ids.size();
    int i, id;

    for(i = 0; i < n; ++i)
    {
        id = ids[i];
        QSharedPointer<Line> & line = mLines[id];
        line->extend(xs[i], ys[i], scalars[i]);
    }
}

const LineVector & LineCollection::getLines()
{
    return mLines;
}

void LineCollection::lock()
{
    mLock.lock();
}

void LineCollection::prune()
{
    for(int i = mLines.size() - 1; i >= 0; --i)
    {
        if (mLines[i]->dead()) {
            // Overwrite and shrink vector to discard; no need to swap.
            mLines[i] = mLines.last();
            mLines.pop_back();
        }
    }
}

void LineCollection::reset()
{
    mLines.clear();
}

QString LineCollection::str()
{
    QString str("{\n");

    for(int i = 0; i < mLines.size(); ++i)
    {
        const LinePointer & line = mLines[i];
        const Vector x = line->x();
        const Vector y = line->y();
        const Vector s = line->scalars();
        str.append(QString::asprintf("%d: {\n\t\"len\": %g,\n\t\"n\": %d,\n\t\"xyz\": [ ", i, line->length(), x.size()));

        for(int j = 0; j < x.size(); ++j)
        {
            str.append(QString::asprintf("(%g,%g,%g), ", x[j], y[j], s[j]));
        }
        str.append("]\n}\n");
    }

    str.append("}\n");

    return str;
}

void LineCollection::unlock()
{
    mLock.unlock();
}

}
