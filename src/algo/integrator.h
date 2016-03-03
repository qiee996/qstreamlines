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