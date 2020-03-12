QT += core
QT -= gui

TARGET = Test
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
win32-g++ {
    INCLUDEPATH += C:/boost/boost_mingw_492_32/include/boost-1_71
    LIBS += "-LC:/boost/boost_mingw_492_32/lib" \
                -llibboost_filesystem-mgw49-mt-d-x32-1_71\
                -llibboost_thread-mgw49-mt-d-x32-1_71

}

SOURCES += main.cpp

