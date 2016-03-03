#include "cli.h"
#include <QDebug>
#include <iostream>

namespace qst {

const QString Cli::getOutputPath()
{
    return mParser.value("o");
}

const QString Cli::getProjectFileName()
{
    if (hasProjectFileName()) {
        return mParser.positionalArguments().at(0);
    }
    return "";
}

bool Cli::hasProjectFileName()
{
    return mParser.positionalArguments().size() > 0;
}

bool Cli::isBatch()
{
    return mParser.isSet("o");
}

int Cli::parse(const QStringList & args)
{
    mParser.setApplicationDescription("Streamline gui");
    mParser.addHelpOption();
    mParser.addVersionOption();
    mParser.addPositionalArgument("project", "Project settings file to load.");

    QCommandLineOption debugOption(QStringList() << "d" << "debug",
                                   "Debug level");
    mParser.addOption(debugOption);

    QCommandLineOption firstOption(QStringList() << "f" << "first",
                                   "First frame to export.", "first");
    mParser.addOption(firstOption);

    QCommandLineOption lastOption(QStringList() << "l" << "last",
                                   "Last frame to export.", "last");
    mParser.addOption(lastOption);

    QCommandLineOption outputOption(QStringList() << "o" << "output",
                                  "Output path to export images.", "output");
    mParser.addOption(outputOption);

    mParser.process(args);

    if (mParser.isSet("d")) {
        qSetMessagePattern("%{file}(%{line}): %{message}");
    }

    return 0;
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