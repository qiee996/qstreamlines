#ifndef APP_H
#define APP_H

#include <QApplication>
#include <signal.h>
#include "algo/streamer.h"
#include "control/projectcontrol.h"
#include "control/simanimator.h"
#include "model/cli.h"
#include "model/linecollection.h"
#include "model/project.h"
#include "model/vectorfield.h"
#include "render/glexporter.h"
#include "util/lut.h"
#include "view/mainwindow.h"

#define APP_NAME_STR "qstreamlines"
#define APP_VER_STR "1.0.0"

namespace qst {

class App
{
public:
    App();
    ~App();

    void apply();
    void connect();
    void init();
    static int main(int argc, char *argv[]);
    int processCli();
    int run();
    void signalHandler(int sig);

private:
    Cli mCli;
    GLExporter mExporter;
    LineCollection mLines;
    Lut mLut;
    MainWindow *mMainWindow;
    Project mProject;
    ProjectControl mProjectControl;
    SimAnimator mSimAnimator;
    Lut mSpeedLut;
    Streamer mStreamer;
    VectorField mVectorField;
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