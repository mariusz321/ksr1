#-------------------------------------------------
#
# Project created by QtCreator 2011-11-05T18:04:02
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = keywordSelector
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    ArticleLoader.cpp \
    DiscriminatingExtractor.cpp

HEADERS += \
    ArticleLoader.h \
    KeywordExtractorInterface.h \
    DiscriminatingExtractor.h
