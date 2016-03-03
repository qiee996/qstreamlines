#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "interpolator.h"
#include "util/lut.h"

namespace qst {

class Integrator
{
public:
    Integrator();

    /* Return list of xs, ys, speeds for paths integrated nsteps. */
    void integrate(int nsteps, float stepsize, float speedScale,
                   Vector & xis, Vector & yis,
                   Vector2d & xs, Vector2d & ys, Vector2d & speeds);
    void setInterpolators(Interpolator *ui, Interpolator *vi, Interpolator *si);
    void setSpeedLut(Lut *lut);

private:
    Interpolator *mInterpU, *mInterpV, *mInterpSpeed;
    Lut *mSpeedLut;
};

}

#endif
