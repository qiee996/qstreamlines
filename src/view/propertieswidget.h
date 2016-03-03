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