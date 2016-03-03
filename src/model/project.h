#ifndef PROJECT_H
#define PROJECT_H

#include <QJsonObject>
#include <QVector>

namespace qst {

class Project
{
public:
    float arrowHeight();
    float arrowWidth();
    QVector<float> bgcolor();
    QString bgimage();
    int cap();
    float capPct();
    QString color();
    float decay();
    int framesPerSecond();
    int inject();
    void load(const QString & filename);
    int maxlen();
    int point();
    void save(const QString & filename);
    int screenHeight();
    int screenWidth();
    float speed();
    QString speedlut();
    int steps();
    float stepsize();
    int tiplen();
    QString u();
    QVector<float> uMinMax();
    QString v();
    QVector<float> vMinMax();
    int width();

private:
    void fromJson(const QJsonObject & json);

    QJsonObject mJson;
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