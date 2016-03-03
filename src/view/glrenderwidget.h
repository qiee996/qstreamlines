#ifndef GLRENDERWIDGET_H
#define GLRENDERWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "model/linecollection.h"
#include "render/buffer.h"
#include "render/renderer.h"
#include "util/lut.h"

namespace qst {

class GLRenderWidget : public QOpenGLWidget, protected QOpenGLFunctions, public Renderer
{
    Q_OBJECT
public:
    explicit GLRenderWidget(QWidget *parent = 0);
    ~GLRenderWidget();

    void clear();
    const Buffer & buffer() const;
    int height();
    void readPixels(unsigned char *buffer);
    void render();
    void setBgColor(const QVector<float> & rgba);
    void setBgImage(const QString & fn);
    void setLinesModel(LineCollection *model);
    void setLut(Lut *lut);
    void setSize(int w, int h);
    int width();

signals:

public slots:
    void setArrowHeight(float h);
    void setArrowHeight(QString h);
    void setArrowWidth(QString w);
    void setArrowWidth(float w);
    void setCapPct(QString pct);
    void setCapPct(float pct);
    void setCapWidth(int w);
    void setLineWidth(int w);
    void setPointSize(int s);
    void setShowArrows(int show);
    void setShowLines(int show);
    void setShowPoints(int show);

protected:
    void grab();
    void initializeGL();
    void paintArrows();
    void paintBackgroundImage();
    void paintGL();
    void paintLines();
    void paintPoints();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

private:
    float mArrowHeight;
    float mArrowWidth;
    QVector<float> mBgColor;
    QImage mBgImage;
    // For exporting image.
    Buffer mBuffer;
    int mCapWidth;
    float mCapPct;
    int mHeight;
    LineCollection *mLinesModel;
    int mLineWidth;
    Lut *mLut;
    int mPointSize;
    bool mShowArrows;
    bool mShowLines;
    bool mShowPoints;
    int mWidth;
};

}
#endif
