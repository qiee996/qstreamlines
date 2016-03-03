#ifndef CLI_H
#define CLI_H

#include <QCommandLineParser>

namespace qst {

class Cli
{
public:
    const QString getProjectFileName();
    const QString getOutputPath();
    bool hasProjectFileName();
    bool isBatch();
    int parse(const QStringList & args);

private:
    QCommandLineParser mParser;
};

}

#endif
