#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QMainWindow>
#include "view/propertieswidget.h"
#include "view/glrenderwidget.h"

namespace qst {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    GLRenderWidget* getGLRenderWidget();
    PropertiesWidget* getPropertiesWidget();

public slots:
    void onRenderResized();
    void onResizeRender(int w, int h);

signals:
    void closed();

protected:
    void closeEvent(QCloseEvent *e);

private:
    void createMenus();
    void createPropertiesWidget();
    void createRenderWidget();
    void createWidgets();

    GLRenderWidget *mGLRenderWidget;
    PropertiesWidget *mProperties;
};

}
#endif // MAINWINDOW_H
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