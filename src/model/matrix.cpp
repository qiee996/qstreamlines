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
