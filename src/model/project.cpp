#include "model/project.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

namespace qst {

float Project::arrowHeight()
{
    return mJson["glyph"].toObject()["arrowHeight"].toDouble();
}

float Project::arrowWidth()
{
    return mJson["glyph"].toObject()["arrowWidth"].toDouble();
}

QVector<float> Project::bgcolor()
{
    QVector<float> rgba;
    const QJsonArray & a = mJson["background"].toObject()["color"].toArray();
    rgba.append(a[0].toDouble());
    rgba.append(a[1].toDouble());
    rgba.append(a[2].toDouble());
    rgba.append(a[3].toDouble());
    return rgba;
}

QString Project::bgimage()
{
    return mJson["background"].toObject()["image"].toString();
}

int Project::cap()
{
    return mJson["glyph"].toObject()["cap"].toInt();
}

float Project::capPct()
{
    return mJson["glyph"].toObject()["capPct"].toDouble();
}

QString Project::color()
{
    return mJson["color"].toString();
}

float Project::decay()
{
    return mJson["glyph"].toObject()["decay"].toDouble();
}

int Project::framesPerSecond()
{
    return mJson["framesPerSecond"].toInt();
}

void Project::fromJson(const QJsonObject & json)
{
    mJson = json;
}

int Project::inject()
{
    return mJson["streamer"].toObject()["inject"].toInt();
}

void Project::load(const QString & filename)
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
    this->fromJson(jsondoc.object());
}

int Project::maxlen()
{
    return mJson["glyph"].toObject()["maxlen"].toInt();
}

int Project::point()
{
    return mJson["glyph"].toObject()["point"].toInt();
}

void Project::save(const QString & filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open file=%s", filename.toStdString().c_str());
        return;
    }

    QJsonDocument jsondoc(mJson);
    file.write(jsondoc.toJson(QJsonDocument::Indented));
    file.close();
}

int Project::screenHeight()
{
    return mJson["screenWidthHeight"].toArray()[1].toInt();
}

int Project::screenWidth()
{
    return mJson["screenWidthHeight"].toArray()[0].toInt();
}

float Project::speed()
{
    return mJson["streamer"].toObject()["speed"].toDouble();
}

QString Project::speedlut()
{
    return mJson["streamer"].toObject()["speedlut"].toString();
}

int Project::steps()
{
    return mJson["streamer"].toObject()["steps"].toInt();
}

float Project::stepsize()
{
    return mJson["streamer"].toObject()["size"].toDouble();
}

int Project::tiplen()
{
    return mJson["glyph"].toObject()["tiplen"].toInt();
}

QString Project::u()
{
    return mJson["u"].toObject()["file"].toString();
}

QVector<float> Project::uMinMax()
{
    QVector<float> minmax;
    const QJsonArray & a = mJson["u"].toObject()["validMinMax"].toArray();
    minmax.append(a[0].toDouble());
    minmax.append(a[1].toDouble());
    return minmax;
}

QString Project::v()
{
    return mJson["v"].toObject()["file"].toString();
}

QVector<float> Project::vMinMax()
{
    QVector<float> minmax;
    const QJsonArray & a = mJson["v"].toObject()["validMinMax"].toArray();
    minmax.append(a[0].toDouble());
    minmax.append(a[1].toDouble());
    return minmax;
}

int Project::width()
{
    return mJson["glyph"].toObject()["width"].toInt();
}

}
