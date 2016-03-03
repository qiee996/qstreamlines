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
