#ifndef PROPERTIESWIDGET_H
#define PROPERTIESWIDGET_H

#include <QCheckBox>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

namespace qst {

class PropertiesWidget : public QWidget
{
    Q_OBJECT
public:
    PropertiesWidget(QWidget *parent = 0);
    QSpinBox* getFrameRateWidget();

    QCheckBox *mArrowShow;
    QLineEdit *mArrowHeight;
    QLineEdit *mArrowWidth;
    QSpinBox *mCapWidth;
    QLineEdit *mCapPct;
    QLineEdit *mColor;
    QLineEdit *mDecay;
    QSpinBox *mFps;
    QSpinBox *mInject;
    QCheckBox *mLineShow;
    QSpinBox *mMaxlen;
    QPushButton *mPlay;
    QSpinBox *mPointSize;
    QCheckBox *mPointShow;
    QPushButton *mReset;
    QSpinBox *mScreenH;
    QSpinBox *mScreenW;
    QSpinBox *mSteps;
    QLineEdit *mSpeed;
    QLineEdit *mStepsize;
    QSpinBox *mTiplen;
    QLineEdit *mU;
    QLineEdit *mV;
    QSpinBox *mWidth;

signals:
    void play();
    void reset();
    void resizeRender(int w, int h);
    void stop();

public slots:
    void onPlay();
    void onReset();
    void onResizeRender();

protected:
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
};

}
#endif
