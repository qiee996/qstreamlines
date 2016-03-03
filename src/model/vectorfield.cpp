#include "model/vectorfield.h"
#include <math.h>
#include <QDebug>

namespace qst {

void VectorField::computeSpeed()
{
    if (empty()) {
        return;
    }

    Matrix & speed = mSpeed.matrix();
    Matrix & u = mU.matrix();
    Matrix & v = mV.matrix();

    int nx, ny, i, j;
    float uu, vv;
    mU.shape(nx, ny);
    speed.resize(nx, ny);

    for(i = 0; i < ny; ++i) {
        for(j = 0; j < nx; ++j) {
            uu = u.at(i, j);
            vv = v.at(i, j);
            speed.assign(i, j, sqrt(uu*uu + vv*vv));
        }
    }
}

bool VectorField::empty()
{
    return mU.empty() || mV.empty();
}

void VectorField::load(QString ufilename, QVector<float> uMinMax,
                       QString vfilename, QVector<float> vMinMax)
{
    mU.load(ufilename);
    mU.matrix().setValidRange(uMinMax[0], uMinMax[1]);
    mV.load(vfilename);
    mV.matrix().setValidRange(vMinMax[0], vMinMax[1]);
    computeSpeed();
}

void VectorField::random(float & x, float & y, float & u, float & v)
{
    mU.random(x, y, u);
    mV.random(x, y, v);
}

Field & VectorField::speed()
{
    return mSpeed;
}

Field & VectorField::u()
{
    return mU;
}

Field & VectorField::v()
{
    return mV;
}

}
