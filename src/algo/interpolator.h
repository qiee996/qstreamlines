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
