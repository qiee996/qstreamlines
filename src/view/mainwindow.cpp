#include "mainwindow.h"
#include <QDebug>
#include <QDockWidget>

namespace qst {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createMenus();
    createWidgets();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    emit closed();
    e->accept();
}

void MainWindow::createMenus()
{

}

void MainWindow::createWidgets()
{
    createRenderWidget();
    createPropertiesWidget();
}

void MainWindow::createRenderWidget()
{
    mGLRenderWidget = new GLRenderWidget(this);
    setCentralWidget(mGLRenderWidget);
    mGLRenderWidget->move(350,0);

    connect(mGLRenderWidget, SIGNAL(resized()),
            this, SLOT(onRenderResized()));
}

void MainWindow::createPropertiesWidget()
{
    QDockWidget *dock = new QDockWidget("Properties", this);
    mProperties = new PropertiesWidget(this);
    dock->setWidget(mProperties);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    dock->setFloating(true);

    connect(mProperties, SIGNAL(resizeRender(int,int)),
            this, SLOT(onResizeRender(int,int)));
}

GLRenderWidget* MainWindow::getGLRenderWidget()
{
    return mGLRenderWidget;
}

PropertiesWidget* MainWindow::getPropertiesWidget()
{
    return mProperties;
}

void MainWindow::onRenderResized()
{
    const QSize & s = mGLRenderWidget->size();

    if (mProperties->mScreenH->value() != s.height()) {
        mProperties->mScreenH->setValue(s.height());
    }

    if (mProperties->mScreenW->value() != s.width()) {
        mProperties->mScreenW->setValue(s.width());
    }
}

void MainWindow::onResizeRender(int w, int h)
{
    const QSize & sizeProp = mProperties->size();
    const QSize & sizeRen = mGLRenderWidget->size();
    const QSize & sizeThis = size();

    if (h != sizeRen.height() || w != sizeRen.width()) {
        mGLRenderWidget->setSize(w, h);
        int wMargin = sizeThis.width() - (sizeProp.width() + sizeRen.width());
        resize(w + wMargin + sizeProp.width(), h);
    }
}

MainWindow::~MainWindow()
{
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