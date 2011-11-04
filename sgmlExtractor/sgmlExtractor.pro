#-------------------------------------------------
#
# Project created by QtCreator 2011-11-04T18:32:25
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = sgmlExtractor
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    SgmlReader.cpp \
    ArticleWriter.cpp

HEADERS += \
    SgmlReader.h \
    ArticleWriter.h




