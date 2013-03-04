
QT       += opengl
CONFIG   += console

TARGET = simplescene

TEMPLATE = app
INCLUDEPATH += ./include

SOURCES += main.cpp \
    mainview.cpp \
    glslprogram.cpp \
    simplescene.cpp \
    gl3w.c

HEADERS += \
    mainview.h \
    scene.h \
    glslprogram.h \
    simplescene.h

OTHER_FILES += \
    fragment.glsl \
    vertex.glsl



