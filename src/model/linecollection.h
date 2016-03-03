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
/*
    LICENSE BEGIN

    qstreamlines - Realtime streamlines animator.
    Copyright (C) 2016  Remik Ziemlinski

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    LICENSE END
*/