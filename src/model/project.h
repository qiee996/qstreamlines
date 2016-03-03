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
