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
