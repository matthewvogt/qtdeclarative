load(qttest_p4)
contains(QT_CONFIG,declarative): QT += declarative network widgets
macx:CONFIG -= app_bundle

SOURCES += tst_qdeclarativeincubator.cpp \
           testtypes.cpp
HEADERS += testtypes.h

DEFINES += SRCDIR=\\\"$$PWD\\\"

CONFIG += parallel_test

QT += core-private gui-private v8-private declarative-private
