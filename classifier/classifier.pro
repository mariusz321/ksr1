#-------------------------------------------------
#
# Project created by QtCreator 2011-10-24T19:48:27
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = classifier
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -mtune=native -march=native -std=c++0x

SOURCES += main.cpp \
    tfidf.cpp \
    knnthread.cpp \
    knn.cpp \
    sgmlreader.cpp \
    knnsimilaritythread.cpp \
    EuclideanMetric.cpp \
    MetricInterface.cpp \
    MetricFactory.cpp \
    ManhattanMetric.cpp \
    ChebyshevMetric.cpp \
    NormalizedMetric.cpp \
    VectorLoader.cpp \
    NGramLoader.cpp \
    NGramMetric.cpp \
    MIKeywordLoader.cpp \
    KeywordLoaderInterface.cpp

HEADERS += \
    tfidf.h \
    knnthread.h \
    knn.h \
    sgmlreader.h \
    knnsimilaritythread.h \
    MetricInterface.h \
    EuclideanMetric.h \
    MetricFactory.h \
    ManhattanMetric.h \
    ChebyshevMetric.h \
    NormalizedMetric.h \
    VectorLoader.h \
    Element.h \
    NGramLoader.h \
    NGramMetric.h \
    KeywordLoaderInterface.h \
    MIKeywordLoader.h
