#ifndef MATRIX_H
#define MATRIX_H

#include <limits>
#include <string>
#include "common/types.h"

#define FLOAT32INF std::numeric_limits<float>::infinity()

namespace qst {

class Matrix
{
public:
    Matrix();
    Matrix(int nx, int ny, float validmin=-FLOAT32INF, float validmax=FLOAT32INF);

    void assign(int row, int col, float value);
    float at(int row, int col);
    bool empty();
    bool isValid(float value);
    int numRows();
    int numColumns();
    void resize(int nx, int ny);
    void setValidRange(float vmin, float vmax);
    QString toString();

private:
    Vector2d mMatrix;
    float mValidMin, mValidMax;
    int mNx, mNy;
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