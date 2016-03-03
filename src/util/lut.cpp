#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "util/lut.h"

namespace qst {

void Lut::add(float x, Vector & row)
{
    Vector newRow;
    newRow.append(x);
    newRow.append(row);

    mPts.append(newRow);
}

void Lut::build()
{
    int npts = mPts.size();
    mTable.clear();
    mTable.resize(mSize);

    mTable.back() = mPts.back().mid(1);

    for(int pUpper = 1; pUpper < npts; ++pUpper)
    {
        int pLower = pUpper - 1;
        int tLower = int(mPts[pLower][0] * mSize);
        int tUpper = int(mPts[pUpper][0] * mSize);

        for(int t = tLower; t < tUpper; ++t)
        {
            float w = float(t - tLower) / (tUpper - tLower);
            mTable[t] = lerp(mPts[pLower].mid(1),
                             mPts[pUpper].mid(1), w);
        }
    }
}

Vector Lut::lerp(const Vector & a, const Vector & b, float weight)
{
    int n = a.size();
    Vector result;
    result.resize(n);

    for(int i = 0; i < n; ++i)
    {
        result[i] = (a[i]*(1.0-weight) + b[i]*weight);
    }

    return result;
}

void Lut::load(const QString & filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file=%s", filename.toStdString().c_str());
        return;
    }

    QJsonDocument jsondoc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!jsondoc.isObject()) {
        qWarning("Expected json object. Invalid file=%s",
                 filename.toStdString().c_str());
        return;
    }

    const QJsonObject & json = jsondoc.object();

    if (json.contains("size")) {
        mSize = json["size"].toInt();
    }

    if (json.contains("range")) {
        const QJsonArray & minmax = json["range"].toArray();
        mMin = minmax[0].toDouble();
        mMax = minmax[1].toDouble();
        mRange = mMax - mMin;
    }

    if (json.contains("table")) {
        const QJsonArray & table = json["table"].toArray();
        int n = table.size();
        mPts.resize(n);

        for(int i = 0; i < n; ++i)
        {
            const QJsonArray & row = table[i].toArray();
            Vector & pts = mPts[i];
            int m = row.size();
            pts.resize(m);

            for(int j = 0; j < m; ++j)
            {
                pts[j] = row[j].toDouble();
            }
        }
    }

    build();
}

Vector Lut::lookup(float x)
{
    if (x <= mMin) {
        return mPts.front().mid(1);
    }

    if (x >= mMax) {
        return mPts.back().mid(1);
    }

    float numer = x - mMin;
    int i = int(mSize * numer / mRange);

    return mTable[i];
}

float Lut::lookup1(float x)
{
    if (x <= mMin) {
        return mPts.front()[1];
    }

    if (x >= mMax) {
        return mPts.back()[1];
    }

    float numer = x - mMin;
    int i = int(mSize * numer / mRange);

    return mTable[i][0];
}

QString Lut::str()
{
    QString s;
    int n = mTable.size();
    for(int i = 0; i < n; ++i)
    {
        int m = mTable[i].size();
        for(int j = 0; j < m; ++j)
        {
            s.append(QString::asprintf("%g", mTable[i][j]));
        }
    }

    return s;
}

}
