#include "control/projectcontrol.h"

namespace qst {

void ProjectControl::setCli(Cli *cli)
{
    if (!cli) {
        return;
    }

    if (cli->hasProjectFileName()) {
        mProject->load(cli->getProjectFileName());
    }
}

void ProjectControl::updateUi(PropertiesWidget *ui)
{
    if (ui) {
        ui->mArrowHeight->setText(QString::number(mProject->arrowHeight()));
        ui->mArrowShow->setChecked(mProject->arrowHeight());
        ui->mArrowWidth->setText(QString::number(mProject->arrowWidth()));
        ui->mColor->setText(mProject->color());
        ui->mCapPct->setText(QString::number(mProject->capPct()));
        ui->mCapWidth->setValue(mProject->cap());
        ui->mDecay->setText(QString::number(mProject->decay()));
        ui->mFps->setValue(mProject->framesPerSecond());
        ui->mInject->setValue(mProject->inject());
        ui->mMaxlen->setValue(mProject->maxlen());
        ui->mPointShow->setChecked(mProject->point());
        ui->mPointSize->setValue(mProject->point());
        ui->mStepsize->setText(QString::number(mProject->stepsize()));
        ui->mScreenH->setValue(mProject->screenHeight());
        ui->mScreenW->setValue(mProject->screenWidth());
        ui->mSpeed->setText(QString::number(mProject->speed()));
        ui->mSteps->setValue(mProject->steps());
        ui->mTiplen->setValue(mProject->tiplen());
        ui->mU->setText(mProject->u());
        ui->mV->setText(mProject->v());
        ui->mWidth->setValue(mProject->width());
    }
}

void ProjectControl::setProject(Project *p)
{
    mProject = p;
}

}
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