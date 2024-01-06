QT += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += wall
CONFIG += werror
CONFIG += wextra
CONFIG += optimize_full

win32 {
    LIBS += -lopengl32
    CONFIG += windows
}

linux {
    LIBS += -lGL
    CONFIG += linux
}

mac {
    LIBS += -framework OpenGL
    CONFIG += macx
}

RESOURCES += resources/resources.qrc

include(src/external/QtGifImage/src/gifimage/qtgifimage.pri)

# Uncomment the following line to make your code fail to compile if it uses deprecated APIs.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000 # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cc \
    src/lib/parser.cc \
    src/view/opengl.cc \
    src/view/viewer.cc

HEADERS += \
    src/lib/struct.h \
    src/lib/parser.h \
    src/view/opengl.h \
    src/view/viewer.h \
    third_party/earcut/earcut.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    src/view/viewer.ui
