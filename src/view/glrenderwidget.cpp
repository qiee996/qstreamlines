#include <math.h>
#include <QDebug>
#include <QGLWidget>
#include "glrenderwidget.h"
#include "model/linecollection.h"
#include "render/arrow.h"
#include "render/glexporter.h"

namespace qst {

GLRenderWidget::GLRenderWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    mArrowHeight(.01), mArrowWidth(.005),
    mCapWidth(0), mCapPct(9999.0),
    mHeight(400), mLinesModel(0), mLineWidth(1),
    mShowLines(true), mShowPoints(true),
    mWidth(400)
{
    mBgColor.append(0);
    mBgColor.append(0);
    mBgColor.append(0);
    mBgColor.append(0);
 }

GLRenderWidget::~GLRenderWidget()
{
}

const Buffer & GLRenderWidget::buffer() const
{
    return mBuffer;
}

void GLRenderWidget::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(mBgColor[0], mBgColor[1], mBgColor[2], mBgColor[3]);
}

void GLRenderWidget::grab()
{
    mBuffer.adjust(4, mWidth, mHeight);
    glReadPixels(0, 0, mWidth, mHeight,
                 GL_RGBA, GL_UNSIGNED_BYTE, mBuffer.bytes());
}

int GLRenderWidget::height()
{
    return mHeight;
}

void GLRenderWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // Enable transparency.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Sets origin as lower-left corner.
    glOrtho(0.0, 1.0, 0.0, 1.0, 0.0, -1.0);

    glDepthFunc(GL_LEQUAL);
    glUseProgram(0);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

QSize GLRenderWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

void GLRenderWidget::paintGL()
{
    clear();
    paintBackgroundImage();

    if (mLinesModel) {
        mLinesModel->lock();
        if (mShowArrows) {
            paintArrows();
        }
        if (mShowLines) {
            paintLines();
        }
        if (mShowPoints) {
            paintPoints();
        }
        mLinesModel->unlock();
    }

    grab();
}

void GLRenderWidget::paintBackgroundImage()
{
    if (mBgImage.isNull()) {
        return;
    }

    glRasterPos2i(0, 0);
    glDrawPixels(mBgImage.width(), mBgImage.height(),
                 GL_BGRA, GL_UNSIGNED_BYTE, mBgImage.bits());
}

void GLRenderWidget::paintArrows()
{
    QVector<float> arrow(6);
    const float *vertsPtr = NULL;
    const LineVector & lines = mLinesModel->getLines();
    int nlines = lines.size();
    float screenRatio = mHeight / (float)mWidth;
    glBegin(GL_TRIANGLES);

    for(int line_i = 0; line_i < nlines; ++line_i)
    {
        const LinePointer & line = lines[line_i];
        if (line.isNull() || line->dead() || line->empty()) {
            continue;
        }

        const QVector<float> & xs = line->x();
        int last = xs.size()-1;
        if (last <= 0) {
            continue;
        }

        const QVector<float> & ys = line->y();

        const Vector & rgba = mLut->lookup(line->scalars()[last]);
        glColor4fv(rgba.data());

        Arrow::create(xs[last-1], ys[last-1],
                      xs[last],   ys[last],
                      mArrowHeight, mArrowWidth, screenRatio, arrow);
        vertsPtr = arrow.data();
        glVertex2fv(vertsPtr);
        glVertex2fv(vertsPtr + 2);
        glVertex2fv(vertsPtr + 4);
    }
    glEnd();
}

void GLRenderWidget::paintLines()
{
    const LineVector & lines = mLinesModel->getLines();
    int nlines = lines.size();
    int pt_i, line_i;

    for(line_i = 0; line_i < nlines; ++line_i)
    {
        const LinePointer & line = lines[line_i];
        if (line.isNull() || line->dead() || line->empty()) {
            continue;
        }

        const QVector<float> & xs = line->x();
        int npts = xs.size();
        if (npts < 2) {
            continue;
        }

        float nptsf = float(npts) - 1.0;
        const QVector<float> & ys = line->y();
        const QVector<float> & scalars = line->scalars();

        Vector rgbaPrev = mLut->lookup(scalars[0]);
        for(pt_i = 1; pt_i < npts; ++pt_i)
        {
            if ((pt_i/nptsf) > mCapPct ) {
                glLineWidth(mLineWidth + mCapWidth);
            } else {
                glLineWidth(mLineWidth);
            }
            Vector rgba = mLut->lookup(scalars[pt_i]);

            // Placed here due to cap width adjustment.
            // LINE_STRIP had endpoint color bleed defect, so must make segments.
            glBegin(GL_LINES);
            glColor4fv(rgbaPrev.data());
            glColor4fv(rgba.data());
            rgbaPrev = rgba;
            glVertex2f(xs[pt_i-1], ys[pt_i-1]);
            glVertex2f(xs[pt_i], ys[pt_i]);
            glEnd();
        }
    }
}

void GLRenderWidget::paintPoints()
{
    glPointSize(mPointSize);

    const LineVector & lines = mLinesModel->getLines();
    int nlines = lines.size();

    glBegin(GL_POINTS);

    for(int line_i = 0; line_i < nlines; ++line_i)
    {
        const LinePointer & line = lines[line_i];
        if (line.isNull() || line->dead() || line->empty()) {
            continue;
        }

        const QVector<float> & xs = line->x();
        int last = xs.size()-1;
        if (last <= 0) {
            continue;
        }

        const Vector & rgba = mLut->lookup(line->scalars()[last]);
        glColor4fv(rgba.data());
        glVertex2f(xs[last], line->y()[last]);
    }

    glEnd();
}

void GLRenderWidget::render()
{
    update(); // This only schedules repaint; it's asynchronous.
}

void GLRenderWidget::readPixels(unsigned char *buffer)
{
    if (buffer) {
        glReadPixels(0, 0, mWidth, mHeight, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    }
}

void GLRenderWidget::resizeGL(int width, int height)
{
    mWidth = width;
    mHeight = height;
    glViewport(0, 0, width, height);

    // Scale background image pixels so entire widget is filled.
    glPixelZoom(width / (double) mBgImage.width(),
                height / (double) mBgImage.height());
}

void GLRenderWidget::setArrowHeight(float h)
{
    mArrowHeight = h;
}

void GLRenderWidget::setArrowHeight(QString h)
{
    mArrowHeight = h.toFloat();
}

void GLRenderWidget::setArrowWidth(float w)
{
    mArrowWidth = w;
}

void GLRenderWidget::setArrowWidth(QString w)
{
    mArrowWidth = w.toFloat();
}

void GLRenderWidget::setCapPct(float pct)
{
    mCapPct = pct;
}

void GLRenderWidget::setCapPct(QString pct)
{
    mCapPct = pct.toFloat();
}

void GLRenderWidget::setCapWidth(int size)
{
    mCapWidth = size;
}

void GLRenderWidget::setLinesModel(LineCollection *model)
{
    mLinesModel = model;
}

void GLRenderWidget::setLut(Lut *lut)
{
    mLut = lut;
}

QSize GLRenderWidget::sizeHint() const
{
    return QSize(mWidth, mHeight);
}

void GLRenderWidget::setBgColor(const QVector<float> & rgba)
{
    mBgColor.clear();
    mBgColor.append(rgba);
}

void GLRenderWidget::setBgImage(const QString & fn)
{
    if (fn.isEmpty()) {
        return;
    }

    mBgImage = QImage(fn).mirrored();;
}

void GLRenderWidget::setLineWidth(int w)
{
    mLineWidth = w;
}

void GLRenderWidget::setPointSize(int s)
{
    mPointSize = s;
}

void GLRenderWidget::setShowArrows(int show)
{
    mShowArrows = show == Qt::Checked;
}

void GLRenderWidget::setShowLines(int show)
{
    mShowLines = show == Qt::Checked;
}

void GLRenderWidget::setShowPoints(int show)
{
    mShowPoints = show == Qt::Checked;
}

void GLRenderWidget::setSize(int w, int h)
{
    mWidth = w;
    mHeight = h;
    resize(w, h);
}

int GLRenderWidget::width()
{
    return mWidth;
}

}
