#ifndef SIMANIMATOR_H
#define SIMANIMATOR_H

#include <QObject>
#include <QThread>
#include <time.h>
#include "algo/sim.h"
#include "render/exporter.h"
#include "render/renderer.h"
#include "util/stopwatch.h"

namespace qst {

class SimAnimator : public QObject
{
    Q_OBJECT
public:
    explicit SimAnimator(QObject *parent=0);
    ~SimAnimator();

    void computeFillTime();
    void setExporter(Exporter *exporter);
    void setRenderer(Renderer *renderer);
    void setSim(Sim *sim);
    void sleepFillTime();

public slots:
    void reset();
    void run();
    void setFramesPerSecond(int fps);
    void start();
    void stop();

signals:
    void stepDone();

protected:
    void computeAverageElapsed();

private:
    bool mActive;
    double mElapsedAverage;
    int mElapsedCount;
    double mElapsedTotal;
    Exporter *mExporter;
    double mFillTimeNanos;
    int mRateNanos;
    Renderer *mRenderer;
    Sim *mSim;
    int mStepId;
    StopWatch mStopWatch;
    QThread mThread;
};

}
#endif

