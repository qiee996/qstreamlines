#ifndef VECTORFIELD_H
#define VECTORFIELD_H

#include "model/field.h"
#include <QString>
#include <QVector>

namespace qst {

class VectorField
{
public:
    void computeSpeed();
    bool empty();
    void load(QString ufilename, QVector<float> uMinMax,
              QString vfilename, QVector<float> vMinMax);
    void random(float & x, float & y, float & u, float & v);
    Field & speed();
    Field & v();
    Field & u();

private:
    Field mU, mV, mSpeed;
};

}
#endif
