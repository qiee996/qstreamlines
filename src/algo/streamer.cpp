#include "streamer.h"
#include <QDebug>

namespace qst {

Streamer::Streamer() : mLines(0), mVectorField(0)
{
}

void Streamer::advance()
{
    if (mLines) {
        mLines->lock();
        inject();
        extend();
        mLines->decay();
        mLines->prune();
//        qDebug().noquote() << mLines->str();
        mLines->unlock();
    }
}

void Streamer::extend()
{
    Vector xis, yis;
    Vector2d xs, ys, speeds;
    QVector<int> ids;

    mLines->endpoints(xis, yis, ids);
    mIntegrator.integrate(mSteps, mStepsize, mSpeedScale,
                          xis, yis, xs, ys, speeds);
    mLines->extend(xs, ys, speeds, ids);
}

void Streamer::inject()
{
    if (!mLines || mVectorField->empty()) {
        return;
    }

    float x,y,u,v;

    for(int i = 0; i < mInject; ++i)
    {
        mVectorField->random(x, y, u, v);
        mLines->add(x, y, sqrt(u*u + v*v), mDecay, mMaxlen, mTiplen);
    }
}

void Streamer::reset()
{
    if (mLines) {
        mLines->lock();
        mLines->reset();
        mLines->unlock();
    }
}

void Streamer::setDecay(float d)
{
    mDecay = d;
}

void Streamer::setDecay(QString d)
{
    mDecay = d.toFloat();
}

void Streamer::setInject(int i)
{
    mInject = i;
}

void Streamer::setLines(LineCollection *lines)
{
    mLines = lines;
}

void Streamer::setMaxlen(int m)
{
    mMaxlen = m;
}

void Streamer::setSpeed(float s)
{
    mSpeedScale = s;
}

void Streamer::setSpeed(const QString & s)
{
    mSpeedScale = s.toFloat();
}

void Streamer::setSpeedLut(Lut *lut)
{
    mIntegrator.setSpeedLut(lut);
}

void Streamer::setSteps(int s)
{
    mSteps = s;
}

void Streamer::setStepsize(float s)
{
    mStepsize = s;
}

void Streamer::setStepsize(const QString & s)
{
    mStepsize = s.toFloat();
}

void Streamer::setTiplen(int t)
{
    mTiplen = t;
}

void Streamer::setVectorField(VectorField *field)
{
    mVectorField = field;

    if (field) {
        mIntegrator.setInterpolators(
                    & field->u().interpolator(),
                    & field->v().interpolator(),
                    & field->speed().interpolator());
    }
}

}
