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
