#ifndef EXPORTER_H
#define EXPORTER_H

#include <QString>

namespace qst {

class Exporter
{
public:
    Exporter();

    void setEnabled(bool enable);
    void setOutputPath(const QString & str);
    virtual void write(int frameid) = 0;

protected:
    bool mEnabled;
    QString mOutputPath;
};

}
#endif

