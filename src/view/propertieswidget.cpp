#include "propertieswidget.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QDebug>

namespace qst {

PropertiesWidget::PropertiesWidget(QWidget *parent) : QWidget(parent)
{
    mArrowHeight = new QLineEdit(this);
    mArrowWidth = new QLineEdit(this);
    mArrowShow = new QCheckBox(this);
    mCapWidth = new QSpinBox(this);
    mCapPct = new QLineEdit(this);
    mColor = new QLineEdit(this);
    mDecay = new QLineEdit(this);
    mFps = new QSpinBox(this);
    mInject = new QSpinBox(this);
    mLineShow = new QCheckBox(this);
    mMaxlen = new QSpinBox(this);
    mPointShow = new QCheckBox(this);
    mPointSize = new QSpinBox(this);
    mScreenH = new QSpinBox(this);
    mScreenW = new QSpinBox(this);
    mSpeed = new QLineEdit(this);
    mSteps = new QSpinBox(this);
    mStepsize = new QLineEdit(this);
    mTiplen = new QSpinBox(this);
    mU = new QLineEdit(this);
    mV = new QLineEdit(this);
    mWidth = new QSpinBox(this);

    mArrowShow->setCheckState(Qt::Unchecked);

    mDecay->setText("1.0");

    mCapWidth->setMinimum(0);

    mFps->setRange(1, 60);
    mFps->setSingleStep(10);
    mFps->setSuffix(" fps");

    mInject->setMinimum(0);
    mInject->setSingleStep(10);

    mLineShow->setCheckState(Qt::Checked);

    mMaxlen->setRange(1, 10000);
    mMaxlen->setSingleStep(10);

    mPointShow->setCheckState(Qt::Unchecked);

    mPointSize->setMinimum(0);
    mPointSize->setSingleStep(1);

    mScreenH->setRange(100,10000);
    mScreenH->setSingleStep(100);

    mScreenW->setRange(100,10000);
    mScreenW->setSingleStep(100);

    mSteps->setMinimum(1);
    mSteps->setSingleStep(10);

    mTiplen->setRange(1, 10000);
    mTiplen->setSingleStep(10);

    mWidth->setRange(1,10);

    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->setLabelAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    formLayout->addRow("Arrow Show:", mArrowShow);
    formLayout->addRow("Arrow Height:", mArrowHeight);
    formLayout->addRow("Arrow Width:", mArrowWidth);
    formLayout->addRow("Cap Width:", mCapWidth);
    formLayout->addRow("Cap Percent:", mCapPct);
    formLayout->addRow("Color:", mColor);
    formLayout->addRow("Decay:", mDecay);
    formLayout->addRow("Frame Rate:", mFps);
    formLayout->addRow("Inject:", mInject);
    formLayout->addRow("Line Width:", mWidth);
    formLayout->addRow("Lines Show:", mLineShow);
    formLayout->addRow("Max Length:", mMaxlen);
    formLayout->addRow("Points Show:", mPointShow);
    formLayout->addRow("Point Size:", mPointSize);
    formLayout->addRow("Screen Height:", mScreenH);
    formLayout->addRow("Screen Width:", mScreenW);
    formLayout->addRow("Speed:", mSpeed);
    formLayout->addRow("Steps:", mSteps);
    formLayout->addRow("Stepsize:", mStepsize);
    formLayout->addRow("Tip Length:", mTiplen);
    formLayout->addRow("U File:", mU);
    formLayout->addRow("V File:", mV);

    mPlay = new QPushButton("Play");
    mReset = new QPushButton("Reset");
    mPlay->setFixedWidth(80);
    mReset->setFixedWidth(80);
    QHBoxLayout *hb = new QHBoxLayout();
    hb->addWidget(mPlay);
    hb->addWidget(mReset);
    formLayout->addRow("", hb);

    setLayout(formLayout);

    setMaximumWidth(300);

    connect(mPlay, SIGNAL(clicked()), this, SLOT(onPlay()));
    connect(mReset, SIGNAL(clicked()), this, SLOT(onReset()));
    connect(mScreenH, SIGNAL(valueChanged(int)), this, SLOT(onResizeRender()));
    connect(mScreenW, SIGNAL(valueChanged(int)), this, SLOT(onResizeRender()));
}

QSpinBox* PropertiesWidget::getFrameRateWidget()
{
    return mFps;
}

QSize PropertiesWidget::minimumSizeHint() const
{
    return QSize(300, 700);
}

void PropertiesWidget::onPlay()
{
    if (mPlay->text() == "Play") {
        mPlay->setText("Stop");
        emit play();
    } else {
        mPlay->setText("Play");
        emit stop();
    }
}

void PropertiesWidget::onReset()
{
    emit reset();
}

void PropertiesWidget::onResizeRender()
{
    int h = mScreenH->value();
    int w = mScreenW->value();
    emit resizeRender(w, h);
}

QSize PropertiesWidget::sizeHint() const
{
    return minimumSizeHint();
}

}
