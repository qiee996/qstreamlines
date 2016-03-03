#include "exporter.h"

namespace qst {

Exporter::Exporter() : mEnabled(false)
{
}

void Exporter::setEnabled(bool enable)
{
    mEnabled = enable;
}

void Exporter::setOutputPath(const QString & str)
{
    mOutputPath = str;
}

}
