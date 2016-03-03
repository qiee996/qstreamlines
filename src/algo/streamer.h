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
