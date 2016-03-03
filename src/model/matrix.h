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
