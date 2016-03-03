#include "arrow.h"
#include <QDebug>
#include <QVector2D>

namespace qst {

void Arrow::create(
        float fromX, float fromY, float toX, float toY,
        float h, float w, float screenRatio,
        QVector<float> & xy)
{
    QVector3D dir(toX - fromX, toY - fromY, 0.0);
    dir.normalize();
    QVector3D ort = QVector3D::crossProduct(dir, QVector3D(0, 0, -1));
    ort.normalize();

    QVector2D ort2(ort.x()*screenRatio*screenRatio, ort.y());
    ort2.normalize();
    float t = atan2(ort2.y(), ort2.x());
    float ox = ort2.x() * w * pow(screenRatio, fabs(cos(t)));
    float oy = ort2.y() * w;

    float shear = h * pow(screenRatio, fabs(pow( sin(t), 8) ));
    xy[0] =  dir.x() * shear + toX;
    xy[1] =  dir.y() * shear + toY;
    xy[2] =  ox + toX;
    xy[3] =  oy + toY;
    xy[4] = -ox + toX;
    xy[5] = -oy + toY;
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