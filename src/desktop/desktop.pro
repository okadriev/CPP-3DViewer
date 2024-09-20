QT += core gui opengl widgets openglwidgets

#INCLUDEPATH += $$[QT_INSTALL_HEADERS]

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    figure.cpp \
    main.cpp \
    mainwindow.cpp \
    ../gif/gif.cpp \
    ../obj/model_info.cpp \
    ../obj/setting_info.cpp \
    ../obj/obj.cpp \
    myopenglrenderer.cpp \
    point.cpp

HEADERS += \
    figure.h \
    mainwindow.h \
    ../gif/gif.hpp \
    ../obj/obj.hpp \
    ../obj/model_info.h \
    ../obj/setting_info.h \
    myopenglrenderer.h \
    point.h \
    tiny_obj_loader.h

FORMS += \
    mainwindow.ui

LIBS += -lgif
#LIBS += -lGL -lGLU

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
