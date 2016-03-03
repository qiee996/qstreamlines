#include "glexporter.h"

namespace qst {

GLExporter::GLExporter() : Exporter(), mRenderer(0)
{
}

GLExporter::~GLExporter()
{
}

void GLExporter::setRenderer(GLRenderWidget *ren)
{
    mRenderer = ren;
}

void GLExporter::write(int frameid)
{
    if (mEnabled && mRenderer) {
        QImage img(mRenderer->buffer().bytes(),
                   mRenderer->width(),
                   mRenderer->height(), QImage::Format_RGBA8888);
        QString path(mOutputPath);
        path.append(QString::asprintf("%05d.png", frameid));
        img.mirrored().save(path);
    }
}

}
