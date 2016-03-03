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