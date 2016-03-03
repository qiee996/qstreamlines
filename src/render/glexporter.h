#ifndef GLEXPORTER_H
#define GLEXPORTER_H

#include "render/exporter.h"
#include "view/glrenderwidget.h"

namespace qst {

class GLExporter : public Exporter
{
public:
    GLExporter();
    ~GLExporter();

    void setRenderer(GLRenderWidget *ren);
    void write(int frameid=0);

private:
    GLRenderWidget *mRenderer;
};

}

#endif
