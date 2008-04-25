TEMPLATE = app
CONFIG += qt debug
INCLUDEPATH += . /usr/include/kde
LIBS += -L/usr/lib/kde3 -lkdeui -lkio

HEADERS += dialog.h
SOURCES += dialog.cpp
SOURCES += main.cpp
