#-------------------------------------------------
#
# Project created by QtCreator 2011-10-24T19:48:27
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = KSR1
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -mtune=native -march=native

SOURCES += main.cpp \
    tfidf.cpp \
    knnthread.cpp \
    knn.cpp \
    sgmlreader.cpp \
    knnsimilaritythread.cpp

HEADERS += \
    tfidf.h \
    knnthread.h \
    knn.h \
    sgmlreader.h \
    knnsimilaritythread.h








