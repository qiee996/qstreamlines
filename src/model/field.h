#ifndef FIELD_H
#define FIELD_H

#include <random>
#include <QString>
#include "model/matrix.h"
#include "algo/interpolator.h"

namespace qst {

class Field
{
public:
    Field();

    bool empty() { return mMatrix.empty(); }
    Interpolator & interpolator();
    Matrix & matrix() { return mMatrix; }
    void load(QString & filename);
    /* Return random point. */
    void random(float & x, float & y, float & value);
    void shape(int & nx, int & ny);

private:
    Interpolator mInterpolator;
    Matrix mMatrix;
    std::default_random_engine mRandGenerator;
    std::uniform_real_distribution<float> mRandDistribution;
};

}
#endif
