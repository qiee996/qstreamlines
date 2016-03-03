#include <QDebug>
#include "model/line.h"

namespace qst {

Line::Line(float decay, int maxlen, int tiplen) :
    mDecay(decay), mFirst(0), mLast(-1), mMaxlen(maxlen),
    mTiplen(tiplen)
{
}

bool Line::dead()
{
    return mX.size() && (mFirst > mLast);
}

void Line::decay()
{
    int n = mX.size();

    if (n < mTiplen) {
        return;
    }

    if (n >= mMaxlen && mTiplen > 0) {
        // Stopped growing, so start shortening tip.
        mTiplen -= 1;
    }

    int lastToFade = mLast - mTiplen;

    for(int i = mFirst; i <= lastToFade; ++i)
    {
        mScalars[i] -= mDecays[i];
    }

    // Prune any points with scalar near zero.
    for(; mFirst <= mLast; ++mFirst)
    {
        if (1e-3 < mScalars[mFirst])
        {
            break;
        } // else keep looking for non-zero scalar.
    }
}

bool Line::extendable()
{
    return mX.size() < mMaxlen;
}

bool Line::empty()
{
    return mX.empty();
}

void Line::extend(float x, float y, float scalar)
{
    mX.append(x);
    mY.append(y);
    mScalars.append(scalar);
    mDecays.push_back(scalar * mDecay);
    mLast = mX.size() - 1;
}

void Line::extend(QVector<float> & xs,
                  QVector<float> & ys,
                  QVector<float> & scalars)
{
    mX.append(xs);
    mY.append(ys);
    mScalars.append(scalars);

    int n = xs.size();
    for(int i = 0; i < n; ++i) {
        mDecays.push_back(scalars[i] * mDecay);
    }

    mLast = mX.size() - 1;
}

float Line::lastX()
{
    return mX.back();
}

float Line::lastY()
{
    return mY.back();
}

float Line::length()
{
    int n = mX.size();
    float len = 0.0;
    float dx, dy;

    for(int i = 1; i < n; ++i)
    {
        dx = mX[i]-mX[i-1];
        dy = mY[i]-mY[i-1];
        len += sqrt(dx*dx + dy*dy);
    }

    return len;
}

int Line::maxlen()
{
    return mMaxlen;
}

const QVector<float> & Line::scalars()
{
    return mScalars;
}

const QVector<float> & Line::x()
{
    return mX;
}

const QVector<float> & Line::y()
{
    return mY;
}

}
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