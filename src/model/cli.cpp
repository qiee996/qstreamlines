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
