QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

ICON = icon/3dviewer.png

include(QtGifImage/src/gifimage/qtgifimage.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cc \
    model/affine.cc \
    model/parser.cc \
    view/opengl.cc \
    view/viewer.cc

HEADERS += \
    model/affine.h \
    model/parser.h \
    view/opengl.h \
    view/viewer.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    view/viewer.ui
