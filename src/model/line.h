#ifndef LINE_H
#define LINE_H

#include <QVector>
#include <QPointF>

namespace qst {

class Line
{
public:
    /** The tip of line does not fade out until stops growing. */
    Line(float decay=.1, int maxlen=100, int tiplen=10);

    /* True if all points have decayed to zero. */
    bool dead();
    void decay();
    /* False if exceeded max length. */
    bool extendable();
    /* True if has no points. */
    bool empty();
    void extend(float x, float y, float scalar);
    void extend(QVector<float> & xs, QVector<float> & ys,
                QVector<float> & scalars);
    float lastX();
    float lastY();
    float length();
    int maxlen();
    const QVector<float> & scalars();
    void setDecay(float decay) { mDecay = decay; }
    const QVector<float> & x();
    const QVector<float> & y();

private:
    float mDecay;
    QVector<float> mDecays;
    int mFirst;
    int mLast;
    int mMaxlen;
    int mTiplen;
    QVector<float> mX;
    QVector<float> mY;
    QVector<float> mScalars;
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