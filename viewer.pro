QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -Wall -Werror -Wextra -O3 -std=c++17

win32 {
    LIBS += -lopengl32
    CONFIG += windows
}

mac {
    LIBS += -framework OpenGL
    CONFIG += macx
}

linux {
    LIBS += -lGL
    CONFIG += linux
}

CONFIG += c++17

include(src/third_party/earcut/earcut.h);

SOURCES += \
    src/main.cc \
    src/lib/parser.cc \
    src/view/opengl.cc \
    src/view/viewer.cc

HEADERS += \
    src/lib/parser.h \
    src/lib/struct.h \
    src/view/opengl.h \
    src/view/viewer.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    src/view/viewer.ui

RESOURCES += \
    resources/resources.qrc
