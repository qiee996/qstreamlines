#include "model/field.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

namespace qst {

Field::Field()
{
    mInterpolator.setMatrix(& mMatrix);
    mRandGenerator.seed(0); // Make reproducible.
    mRandDistribution = std::uniform_real_distribution<float>(0.0,1.0); // Half open.
}

Interpolator & Field::interpolator()
{
    return mInterpolator;
}

void Field::load(QString & filename)
{
    QFile inputFile(filename);
    QList<QStringList> rows;

    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(& inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine().trimmed();
            if (line.isEmpty()) {
                continue;
            }
            QStringList list = line.split(QRegExp("\\s+"));
            rows.append(list);
        }
        inputFile.close();
    } else {
        qWarning("Failed to open file=%s", filename.toStdString().data());
        return;
    }

    int nx = 0;
    int ny = rows.size();
    if (ny) {
        nx = rows[0].size();
    }

    if (!nx) {
        qWarning("Invalid field data in file=%s", filename.toStdString().data());
        return;
    }

    mMatrix.resize(nx, ny);
    for(int i=0; i < ny; ++i)
    {
        for(int j=0; j < nx; ++j)
        {
            mMatrix.assign(i, j, rows[i][j].toFloat());
        }
    }
}

void Field::random(float & x, float & y, float & value)
{
    int attempts = 10;
    do
    {
        x = mRandDistribution(mRandGenerator);
        y = mRandDistribution(mRandGenerator);
        value = mInterpolator.bilin(x, y);
        if (mMatrix.isValid(value)) {
            return;
        }
    } while (--attempts > 0);

    x = y = value = 0.0;
}

void Field::shape(int & nx, int & ny)
{
    nx = mMatrix.numColumns();
    ny = mMatrix.numRows();
}

}
