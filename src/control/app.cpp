#include <QDebug>
#include "app.h"

namespace qst {

App::App()
{
}

App::~App()
{
    // Do not delete gui window; Qt will do it.
}

void App::apply()
{
    mProjectControl.updateUi(mMainWindow->getPropertiesWidget());
    mMainWindow->getGLRenderWidget()->setBgColor(mProject.bgcolor());
    mMainWindow->getGLRenderWidget()->setBgImage(mProject.bgimage());
    mMainWindow->getGLRenderWidget()->setCapPct(mProject.capPct());
    mMainWindow->getGLRenderWidget()->setCapWidth(mProject.cap());
    mMainWindow->getGLRenderWidget()->setShowArrows(
                mProject.arrowHeight() ? Qt::Checked : Qt::Unchecked);
    mMainWindow->getGLRenderWidget()->setShowPoints(
                mProject.point() ? Qt::Checked : Qt::Unchecked);

    mExporter.setOutputPath(mCli.getOutputPath());
    mExporter.setEnabled(mCli.isBatch());

    mLut.load(mProject.color());
    mSpeedLut.load(mProject.speedlut());
    mStreamer.setDecay(mProject.decay());
    mStreamer.setInject(mProject.inject());
    mStreamer.setMaxlen(mProject.maxlen());
    mStreamer.setSpeed(mProject.speed());
    mStreamer.setSteps(mProject.steps());
    mStreamer.setStepsize(mProject.stepsize());
    mStreamer.setTiplen(mProject.tiplen());
    mVectorField.load(mProject.u(), mProject.uMinMax(),
                      mProject.v(), mProject.vMinMax());
}

void App::connect()
{
    mExporter.setRenderer(mMainWindow->getGLRenderWidget());
    mMainWindow->getGLRenderWidget()->setLinesModel(& mLines);
    mMainWindow->getGLRenderWidget()->setLut(& mLut);
    mProjectControl.setProject(& mProject);
    mStreamer.setLines(& mLines);
    mStreamer.setSpeedLut(& mSpeedLut);
    mStreamer.setVectorField(& mVectorField);
    mSimAnimator.setRenderer(mMainWindow->getGLRenderWidget());
    mSimAnimator.setExporter(& mExporter);
    mSimAnimator.setSim((Sim*) & mStreamer);

    // UI => Streamer
    QObject::connect(mMainWindow->getPropertiesWidget()->mDecay,
                     SIGNAL(textChanged(QString)),
                     & mStreamer, SLOT(setDecay(QString)));
    QObject::connect(mMainWindow->getPropertiesWidget()->mInject,
                     SIGNAL(valueChanged(int)),
                     & mStreamer, SLOT(setInject(int)));
    QObject::connect(mMainWindow->getPropertiesWidget()->mMaxlen,
                     SIGNAL(valueChanged(int)),
                     & mStreamer, SLOT(setMaxlen(int)));
    QObject::connect(mMainWindow->getPropertiesWidget()->mSpeed,
                     SIGNAL(textChanged(QString)),
                     & mStreamer, SLOT(setSpeed(QString)));
    QObject::connect(mMainWindow->getPropertiesWidget()->mSteps,
                     SIGNAL(valueChanged(int)),
                     & mStreamer, SLOT(setSteps(int)));
    QObject::connect(mMainWindow->getPropertiesWidget()->mStepsize,
                     SIGNAL(textChanged(QString)),
                     & mStreamer, SLOT(setStepsize(QString)));
    QObject::connect(mMainWindow->getPropertiesWidget()->mTiplen,
                     SIGNAL(valueChanged(int)),
                     & mStreamer, SLOT(setTiplen(int)));

    // UI => Renderer
    QObject::connect(mMainWindow->getPropertiesWidget()->mArrowShow,
                     SIGNAL(stateChanged(int)),
                     mMainWindow->getGLRenderWidget(), SLOT(setShowArrows(int)));
    QObject::connect(mMainWindow->getPropertiesWidget()->mArrowShow,
                     SIGNAL(stateChanged(int)),
                     mMainWindow->getGLRenderWidget(), SLOT(update()));
    QObject::connect(mMainWindow->getPropertiesWidget()->mArrowHeight,
                     SIGNAL(textChanged(QString)),
                     mMainWindow->getGLRenderWidget(),
                     SLOT(setArrowHeight(QString)));
    QObject::connect(mMainWindow->getPropertiesWidget()->mArrowHeight,
                     SIGNAL(textChanged(QString)),
                     mMainWindow->getGLRenderWidget(), SLOT(update()));
    QObject::connect(mMainWindow->getPropertiesWidget()->mArrowWidth,
                     SIGNAL(textChanged(QString)),
                     mMainWindow->getGLRenderWidget(),
                     SLOT(setArrowWidth(QString)));
    QObject::connect(mMainWindow->getPropertiesWidget()->mArrowWidth,
                     SIGNAL(textChanged(QString)),
                     mMainWindow->getGLRenderWidget(), SLOT(update()));
    QObject::connect(mMainWindow->getPropertiesWidget()->mCapPct,
                     SIGNAL(textChanged(QString)),
                     mMainWindow->getGLRenderWidget(), SLOT(setCapPct(QString)));
    QObject::connect(mMainWindow->getPropertiesWidget()->mCapPct,
                     SIGNAL(textChanged(QString)),
                     mMainWindow->getGLRenderWidget(), SLOT(update()));
    QObject::connect(mMainWindow->getPropertiesWidget()->mCapWidth,
                     SIGNAL(valueChanged(int)),
                     mMainWindow->getGLRenderWidget(), SLOT(setCapWidth(int)));
    QObject::connect(mMainWindow->getPropertiesWidget()->mCapWidth,
                     SIGNAL(valueChanged(int)),
                     mMainWindow->getGLRenderWidget(), SLOT(update()));
    QObject::connect(mMainWindow->getPropertiesWidget()->mWidth,
                     SIGNAL(valueChanged(int)),
                     mMainWindow->getGLRenderWidget(), SLOT(setLineWidth(int)));
    QObject::connect(mMainWindow->getPropertiesWidget()->mWidth,
                     SIGNAL(valueChanged(int)),
                     mMainWindow->getGLRenderWidget(), SLOT(update()));
    QObject::connect(mMainWindow->getPropertiesWidget()->mWidth,
                     SIGNAL(valueChanged(int)),
                     mMainWindow->getGLRenderWidget(), SLOT(update()));
    QObject::connect(mMainWindow->getPropertiesWidget()->mLineShow,
                     SIGNAL(stateChanged(int)),
                     mMainWindow->getGLRenderWidget(), SLOT(setShowLines(int)));
    QObject::connect(mMainWindow->getPropertiesWidget()->mLineShow,
                     SIGNAL(stateChanged(int)),
                     mMainWindow->getGLRenderWidget(), SLOT(update()));
    QObject::connect(mMainWindow->getPropertiesWidget()->mPointSize,
                     SIGNAL(valueChanged(int)),
                     mMainWindow->getGLRenderWidget(), SLOT(setPointSize(int)));
    QObject::connect(mMainWindow->getPropertiesWidget()->mPointSize,
                     SIGNAL(valueChanged(int)),
                     mMainWindow->getGLRenderWidget(), SLOT(update()));
    QObject::connect(mMainWindow->getPropertiesWidget()->mPointShow,
                     SIGNAL(stateChanged(int)),
                     mMainWindow->getGLRenderWidget(), SLOT(setShowPoints(int)));
    QObject::connect(mMainWindow->getPropertiesWidget()->mPointShow,
                     SIGNAL(stateChanged(int)),
                     mMainWindow->getGLRenderWidget(), SLOT(update()));
    QObject::connect(mMainWindow->getPropertiesWidget(), SIGNAL(reset()),
                     mMainWindow->getGLRenderWidget(), SLOT(update()));

    // UI => SimAnimator
    QObject::connect(mMainWindow, SIGNAL(closed()),
                     & mSimAnimator, SLOT(stop()),
                     Qt::DirectConnection);
    QObject::connect(mMainWindow->getPropertiesWidget(), SIGNAL(play()),
                     & mSimAnimator, SLOT(start()),
                     Qt::DirectConnection);
    QObject::connect(mMainWindow->getPropertiesWidget(), SIGNAL(reset()),
                     & mSimAnimator, SLOT(reset()),
                     Qt::DirectConnection);
    QObject::connect(mMainWindow->getPropertiesWidget(), SIGNAL(stop()),
                     & mSimAnimator, SLOT(stop()),
                     Qt::DirectConnection);
    QObject::connect(mMainWindow->getPropertiesWidget()->getFrameRateWidget(),
                     SIGNAL(valueChanged(int)),
                     & mSimAnimator, SLOT(setFramesPerSecond(int)),
                     Qt::DirectConnection);
}

void App::init()
{
    mMainWindow = new MainWindow();
}

int App::processCli()
{
    qApp->setApplicationName(APP_NAME_STR);
    qApp->setApplicationVersion(APP_VER_STR);

    int exitcode = mCli.parse(qApp->arguments());
    if (exitcode) {
        return exitcode;
    }

    mProjectControl.setCli(& mCli);

    return 0;
}

int App::run()
{
    init();
    connect();

    int exitcode = processCli();

    if (exitcode) {
        return exitcode;
    }

    apply();
    mMainWindow->show();
    mMainWindow->onResizeRender(mProject.screenWidth(),
                                mProject.screenHeight());
    return 0;
}

void App::signalHandler(int sig)
{
    switch(sig) {
    case SIGINT:
        mSimAnimator.stop();
        qApp->quit();
        break;
    }
}

int App::main(int argc, char *argv[])
{
    QApplication qt(argc, argv);
    App app;
    int exitcode = app.run();

    if (exitcode) {
        return exitcode;
    }

    return qt.exec();
}

}
