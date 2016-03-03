#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include "model/matrix.h"

namespace qst {

class Interpolator
{
public:
    Interpolator(Matrix *matrix=0);

    /**
     * @brief Bilinear interp 2d matrix.
     * @param x 0..1 coord
     * @param y 0..1 coord
     * @return Interpolated value without checking if in valid range.
     */
    float bilin(float x, float y);

    static float bilin(float q11, float q12, float q21, float q22,
                       float x1, float x2, float y1, float y2,
                       float x, float y);

    void setMatrix(Matrix *matrix);

private:
    Matrix *mMatrix;
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