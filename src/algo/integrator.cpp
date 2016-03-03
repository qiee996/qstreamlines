#include "integrator.h"
#include <QDebug>

namespace qst {

Integrator::Integrator() : mInterpSpeed(0)
{
}

void Integrator::integrate(int nsteps, float stepsize, float speedScale,
                           Vector & xis, Vector & yis,
                           Vector2d & xs, Vector2d & ys, Vector2d & speeds)
{
    int npts = xis.size();
    xs.clear();
    ys.clear();
    speeds.clear();
    // Create storage for output, one path per input point.
    xs.resize(npts);
    ys.resize(npts);
    speeds.resize(npts);

    float k1x, k1y,
          k2x, k2y,
          k3x, k3y,
          k4x, k4y,
          xi, yi, speed, stepsize2, s;

    #define F(XI, YI, X, Y) {                                   \
        s = mInterpSpeed->bilin(XI, YI);                        \
        s = (s == 0 ? 0 : 1.0 / s);                             \
        X = speedScale * s * mInterpU->bilin(XI, YI);           \
        Y = speedScale * s * mInterpV->bilin(XI, YI);           \
    }

    for(int p = 0; p < npts; ++p)
    {
        xi = xis[p];
        yi = yis[p];
        Vector & xsp = xs[p];
        Vector & ysp = ys[p];
        Vector & speedsp = speeds[p];
        xsp.resize(nsteps);
        ysp.resize(nsteps);
        speedsp.resize(nsteps);

        for(int step = 0; step < nsteps; ++step)
        {
            stepsize2 = stepsize * mSpeedLut->lookup1(mInterpSpeed->bilin(xi, yi));
            F(xi, yi, k1x, k1y);
            F(xi + .5*stepsize2*k1x, yi + .5*stepsize2*k1y, k2x, k2y);
            F(xi + .5*stepsize2*k2x, yi + .5*stepsize2*k2y, k3x, k3y);
            F(xi +    stepsize2*k3x, yi +    stepsize2*k3y, k4x, k4y);
            xi += stepsize2*(k1x + 2.0*k2x + 2.0*k3x + k4x) / 6.0;
            yi += stepsize2*(k1y + 2.0*k2y + 2.0*k3y + k4y) / 6.0;
            xsp[step] = xi;
            ysp[step] = yi;
            speed = mInterpSpeed->bilin(xi, yi);
            speedsp[step] = speed;
        }
    }

    #undef F
}

void Integrator::setSpeedLut(Lut *lut)
{
    mSpeedLut = lut;
}

void Integrator::setInterpolators(Interpolator *ui, Interpolator *vi,
                                  Interpolator *si)
{
    mInterpU = ui;
    mInterpV = vi;
    mInterpSpeed = si;
}

}
