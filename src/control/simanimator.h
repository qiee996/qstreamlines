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