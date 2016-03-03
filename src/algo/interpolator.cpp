#include "interpolator.h"
#include <QDebug>

namespace qst {

Interpolator::Interpolator(Matrix *matrix)
{
    setMatrix(matrix);
}

float Interpolator::bilin(float q11, float q12, float q21, float q22,
                           float x1, float x2, float y1, float y2,
                           float x, float y)
{
    float x2x1 = x2 - x1;
    float y2y1 = y2 - y1;
    float x2x = x2 - x;
    float y2y = y2 - y;
    float yy1 = y - y1;
    float xx1 = x - x1;
    return 1.0 / (x2x1 * y2y1) * (
        q11 * x2x * y2y +
        q21 * xx1 * y2y +
        q12 * x2x * yy1 +
        q22 * xx1 * yy1
    );
}

float Interpolator::bilin(float x, float y)
{
    int xmax = mMatrix->numColumns() - 1;
    int ymax = mMatrix->numRows() - 1;
    float xx = xmax * x;
    float yy = ymax * y;

    int x1 = int(xx);
    int x2;
    if (x1 < 0) {
        x1 = x2 = 0;
    } else if (x1 < xmax) {
        x2 = x1 + 1;
    } else {
        x1 = x2 = xmax;
    }

    int y1 = int(yy);
    int y2;
    if (y1 < 0) {
        y1 = y2 = 0;
    } else if (y1 < ymax) {
        y2 = y1 + 1;
    } else {
        y1 = y2 = ymax;
    }

    // qxy
    float q11 = mMatrix->at(y1, x1);
    float q12 = mMatrix->at(y2, x1);
    float q21 = mMatrix->at(y1, x2);
    float q22 = mMatrix->at(y2, x2);

    float x2x = x2 - xx;
    float y2y = y2 - yy;
    float yy1 = yy - y1;
    float xx1 = xx - x1;
    return (
        q11 * x2x * y2y +
        q21 * xx1 * y2y +
        q12 * x2x * yy1 +
        q22 * xx1 * yy1
    );
}

void Interpolator::setMatrix(Matrix *matrix)
{
    mMatrix = matrix;
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