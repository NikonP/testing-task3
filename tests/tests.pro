include(gtest_dependency.pri)

QT += multimedia network

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

HEADERS += \
        configurator_tests.h \
        ../app/configurator.h \
        ../app/radiooooo.h

SOURCES += \
        main.cpp \
        ../app/configurator.cpp \
        ../app/radiooooo.cpp
        
INCLUDEPATH += ../app
