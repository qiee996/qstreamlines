#include "model/matrix.h"
#include <sstream>

namespace qst {

Matrix::Matrix() : mNx(0), mNy(0)
{
    setValidRange(-FLOAT32INF, FLOAT32INF);
}

Matrix::Matrix(int nx, int ny, float validmin, float validmax)
{
    resize(nx, ny);
    setValidRange(validmin, validmax);
}

void Matrix::assign(int row, int col, float value)
{
    mMatrix[row][col] = value;
}

float Matrix::at(int row, int col)
{
    return mMatrix[row][col];
}

bool Matrix::empty()
{
    return mMatrix.empty();
}

bool Matrix::isValid(float value)
{
    return mValidMin <= value && value <= mValidMax;
}

int Matrix::numRows()
{
    return mNy;
}

int Matrix::numColumns()
{
    return mNx;
}

void Matrix::resize(int nx, int ny)
{
    mNx = nx;
    mNy = ny;
    mMatrix.resize(ny);
    for(int i=0; i < ny; ++i) {
        mMatrix[i].resize(nx);
    }
}

void Matrix::setValidRange(float vmin, float vmax)
{
    mValidMin = vmin;
    mValidMax = vmax;
}

QString Matrix::toString()
{
    QString s;
    int nx = numColumns();
    int ny = numRows();

    s.append(QString::asprintf("%g %g\n", mValidMin, mValidMax));

    for(int i = 0; i < ny; ++i) {
        for(int j = 0; j < nx; ++j) {
            s.append(QString::asprintf("%g ", mMatrix[i][j]));
        }
        s += "\n";
    }

    return s;
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