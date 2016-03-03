#ifndef ARROW_H
#define ARROW_H

#include <QVector>
#include <QVector3D>

namespace qst {

class Arrow
{
public:
    /** Return 3 2D vertices for triangle based at toX,toY.
     * @param xy Resize to 6 before calling this function.
    */
    static void create(float fromX, float fromY, float toX, float toY,
                       float height, float width, float screenRatio,
                       QVector<float> & xy);
};

}
#endif
