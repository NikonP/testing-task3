QT += core quick quickcontrols2 multimedia network

TEMPLATE = app
CONFIG += c++11 qt
CONFIG -= app_bundle

SOURCES += main.cpp \
        radiooooo.cpp \
        configurator.cpp

HEADERS += \
    radiooooo.h \
    configurator.h \
    defaults.h
    
RESOURCES += qml.qrc \
    icons.qrc

QMAKE_CFLAGS += -Wall -Wextra -Werror

# gcov
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov
