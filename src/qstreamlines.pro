#-------------------------------------------------
#
# Project created by QtCreator 2016-02-18T14:30:28
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qstreamlines

QMAKE_CXXFLAGS += -std=c++11

SOURCES +=                      \
    algo/integrator.cpp         \
    algo/interpolator.cpp       \
    algo/sim.cpp                \
    algo/streamer.cpp           \
    control/app.cpp             \
    control/projectcontrol.cpp  \
    control/simanimator.cpp     \
    model/cli.cpp               \
    model/field.cpp             \
    model/line.cpp              \
    model/linecollection.cpp    \
    model/matrix.cpp            \
    model/project.cpp           \
    model/vectorfield.cpp       \
    main.cpp                    \
    render/buffer.cpp           \
    render/exporter.cpp         \
    render/glexporter.cpp       \
    util/lut.cpp                \
    util/stopwatch.cpp          \
    view/glrenderwidget.cpp     \
    view/mainwindow.cpp         \
    view/propertieswidget.cpp \
    render/arrow.cpp

HEADERS  +=                     \
    algo/integrator.h           \
    algo/interpolator.h         \
    algo/sim.h                  \
    algo/streamer.h             \
    common/types.h              \
    control/app.h               \
    control/projectcontrol.h    \
    control/simanimator.h       \
    model/cli.h                 \
    model/field.h               \
    model/line.h                \
    model/linecollection.h      \
    model/matrix.h              \
    model/project.h             \
    model/vectorfield.h         \
    render/buffer.h             \
    render/exporter.h           \
    render/glexporter.h         \
    render/renderer.h           \
    util/lut.h                  \
    util/stopwatch.h            \
    view/glrenderwidget.h       \
    view/mainwindow.h           \
    view/propertieswidget.h \
    render/arrow.h

