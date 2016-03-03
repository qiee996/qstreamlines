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