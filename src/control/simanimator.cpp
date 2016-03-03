#include "simanimator.h"
#include <QDebug>

namespace qst {

SimAnimator::SimAnimator(QObject *parent) :
    QObject(parent), mActive(false),
    mElapsedAverage(0.0), mElapsedCount(0), mElapsedTotal(0.0),
    mRateNanos(1e9), mStepId(0)
{
}

SimAnimator::~SimAnimator()
{
    mThread.quit();
    mThread.wait();
}

void SimAnimator::computeAverageElapsed()
{
    mElapsedTotal += mStopWatch.secondsElapsed();
    ++mElapsedCount;

    if (0 == (mElapsedCount % 50))
    {
        mElapsedAverage = mElapsedTotal / mElapsedCount;
        mElapsedCount = 0;
        mElapsedTotal = 0.0;
        //qDebug().nospace() << "averageElapsed=" << mElapsedAverage;
    }
}

void SimAnimator::computeFillTime()
{
    mFillTimeNanos = mRateNanos - 1.0e9*mStopWatch.secondsElapsed();
    if (mFillTimeNanos < 0) {
        mFillTimeNanos = 0;
    }
}

void SimAnimator::run()
{
    while(mActive) {
        mStopWatch.start();
        mSim->advance();
        mRenderer->render();
        // Alternative is to listen for frameSwapped() signal before image write,
        // and not invoke render explicitly, but long after stepDone signal.
        mExporter->write(mStepId);
        mStopWatch.stop();
        emit stepDone();
        computeFillTime();
        computeAverageElapsed();
        sleepFillTime();
        ++mStepId;
    }
}

void SimAnimator::reset()
{
    mSim->reset();
    mStepId = 0;
    emit stepDone();
}

void SimAnimator::setExporter(Exporter *exporter)
{
    mExporter = exporter;
}

void SimAnimator::setFramesPerSecond(int fps)
{
    mRateNanos = 1.0e9/fps;
}

void SimAnimator::setRenderer(Renderer *renderer)
{
    mRenderer = renderer;
}

void SimAnimator::setSim(Sim *sim)
{
    mSim = sim;
}

void SimAnimator::sleepFillTime()
{
    struct timespec t;

    if (mFillTimeNanos >= 1.0e9) {
        t.tv_sec = (long)(mFillTimeNanos / 1.0e9);
        t.tv_nsec = (long)(mFillTimeNanos - 1.0e9);
    } else {
        t.tv_sec = 0;
        t.tv_nsec = (long)mFillTimeNanos;
    }

    nanosleep(& t, 0);
}

void SimAnimator::start()
{
    if (!mActive) {
        mActive = true;
        moveToThread(& mThread);
        connect(& mThread, SIGNAL(started()), this, SLOT(run()));
        mThread.start();
    }
}

void SimAnimator::stop()
{
    disconnect(& mThread, SIGNAL(started()), this, SLOT(run()));
    mActive = false;
    mThread.quit();
}

}
