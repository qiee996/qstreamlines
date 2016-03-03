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