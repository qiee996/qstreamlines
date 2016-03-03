#ifndef STREAMER_H
#define STREAMER_H

#include <QObject>
#include "algo/sim.h"
#include "model/linecollection.h"
#include "model/vectorfield.h"
#include "integrator.h"

namespace qst {

class Streamer : public QObject, public Sim
{
    Q_OBJECT
public:
    Streamer();
    void setLines(LineCollection *lines);
    void setVectorField(VectorField *field);

public slots:
    void advance();
    void reset();
    void setDecay(float d);
    void setDecay(QString d);
    void setInject(int i);
    void setMaxlen(int m);
    void setSpeed(float s);
    void setSpeed(const QString & s);
    void setSpeedLut(Lut *lut);
    void setSteps(int s);
    void setStepsize(float s);
    void setStepsize(const QString & s);
    void setTiplen(int t);

protected:
    void extend();
    void inject();

private:
    float mDecay;
    int mInject;
    int mMaxlen;
    float mSpeedScale;
    int mSteps;
    float mStepsize;
    int mTiplen;

    Integrator mIntegrator;
    LineCollection *mLines;
    VectorField *mVectorField;
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