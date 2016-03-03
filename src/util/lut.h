#ifndef LUT_H
#define LUT_H

#include "common/types.h"

namespace qst {

/** Builds table of interpolated vectors for quick lookup.
 */
class Lut
{
public:
    void add(float x, Vector & row);
    void build();
    void load(const QString & filename);
    Vector lookup(float x);
    float lookup1(float x);
    QString str();

protected:
    Vector lerp(const Vector & a, const Vector & b, float weight);

private:
    float mMax, mMin, mRange;
    short mSize;
    Vector2d mPts;
    Vector2d mTable;
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