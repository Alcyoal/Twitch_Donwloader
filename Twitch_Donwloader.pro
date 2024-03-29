# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = Twitch_Donwloader
DESTDIR = ./x64/Debug
QT += core xml sql opengl network gui svg multimedia uitools location qml webchannel websockets quickwidgets quick openglextensions qmltest quickcontrols2 testlib
QT += widgets
CONFIG += debug console
DEFINES += _UNICODE _ENABLE_EXTENDED_ALIGNED_STORAGE WIN64 QT_DLL QT_LOCATION_LIB QT_MULTIMEDIA_LIB QT_NETWORK_LIB QT_OPENGL_LIB QT_OPENGLEXTENSIONS_LIB QT_QML_LIB QT_QUICK_LIB QT_QUICKWIDGETS_LIB QT_QUICKCONTROLS2_LIB QT_QMLTEST_LIB QT_SQL_LIB QT_SVG_LIB QT_TESTLIB_LIB QT_UITOOLS_LIB QT_WEBCHANNEL_LIB QT_WEBSOCKETS_LIB QT_XML_LIB
INCLUDEPATH += . \
    ./GeneratedFiles/$(ConfigurationName)
LIBS += -lopengl32 \
    -lglu32 \
    -lopencv_world411d
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
HEADERS += ./ScreenshotProvider.h \
    ./InjectedSignaler.h \
    ./HostWindowQML.h \
    ./MouseManager.h
SOURCES += ./main.cpp \
    ./HostWindowQML.cpp \
    ./InjectedSignaler.cpp \
    ./ScreenshotProvider.cpp \
    ./MouseManager.cpp
